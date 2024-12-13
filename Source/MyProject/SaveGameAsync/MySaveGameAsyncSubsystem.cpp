#include "MySaveGameAsyncSubsystem.h"

#include "EngineUtils.h"
#include "Async/Async.h"
#include "MySaveGameAsync.h"
#include "MySaveGameAsyncInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"

void UMySaveGameAsyncSubsystem::LoadGameAsync(FString LoadSlotName)
{
	if (LoadSlotName.IsEmpty()) return;
	
	MySlotName = LoadSlotName;

	if (UGameplayStatics::DoesSaveGameExist(LoadSlotName, 0))
	{
		FAsyncLoadGameFromSlotDelegate LoadGameCallbackDelegate;
		LoadGameCallbackDelegate.BindUObject(this, &UMySaveGameAsyncSubsystem::LoadGameAsyncCallback);
		
		UGameplayStatics::AsyncLoadGameFromSlot(LoadSlotName, 0, LoadGameCallbackDelegate);
	}
	else
	{
		MySaveGameObject = CastChecked<UMySaveGameAsync>(UGameplayStatics::CreateSaveGameObject(UMySaveGameAsync::StaticClass()));
	}
}

void UMySaveGameAsyncSubsystem::SaveGameAsync()
{
	if (bSaving) return;
	
	bSaving = true;

	// broadcast to listeners that we're saving the game
	OnSavingGameAsync.Broadcast(MySlotName, 0, false, bSaving);

	// create a local instance of variables to captured and used in the lambda
	TWeakObjectPtr<UMySaveGameAsyncSubsystem> WeakThis = this; // Alternatively: auto WeakThis = TWeakObjectPtr(this);
	UWorld* World = GetWorld();
	TObjectPtr<UMySaveGameAsync> LocalSaveObject = MySaveGameObject; // maybe create a new one with  CastChecked<UMySaveGameAsync>(UGameplayStatics::CreateSaveGameObject(UMySaveGameAsync::StaticClass()));
	FString SaveSlotName = MySlotName;

	// if you want to get all the actors inside the Async task or use TActorRange you'll have
	// to run the operation on the main thrad with EAsyncExecution::TaskGraphMainThread
	TArray<AActor*> SaveGameActors;
	UGameplayStatics::GetAllActorsWithInterface(World, UMySaveGameAsyncInterface::StaticClass(), SaveGameActors);
	
	Async(EAsyncExecution::Thread, [WeakThis, World, LocalSaveObject, SaveSlotName, SaveGameActors]()
	{
		// clear out content
		LocalSaveObject->MySavedActors.Empty();

		// Alternative: for (AActor* Actor : TActorRange<AActor>(World)) then check if Actor->Implements<UMySaveGameAsyncInterface>(),
		// but since we're inside an Async operation you'll need to use EAsyncExecution::TaskGraphMainThread for TActorRange to work
		for (AActor* Actor : SaveGameActors)
		{
			FMyActorSaveAsyncData ActorData;
			ActorData.Name = Actor->GetFName();
			ActorData.Transform = Actor->GetActorTransform();

			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, *FString::Printf(TEXT("Actor Transform: %s"), *Actor->GetActorTransform().ToString()));
			}
			
			// Use FMemoryWriter wrap the byte array data so it can be FArchive compatible
			FMemoryWriter MyMemoryWriter(ActorData.ByteData);
		
			// Pass the ByteData to the Archive
			FObjectAndNameAsStringProxyArchive Ar(MyMemoryWriter, true);
		
			// Use ArIsSaveGame to indicate the Actor's SaveGame specifiers
			Ar.ArIsSaveGame = true;
			// Serialize the data
			Actor->Serialize(Ar);
		
			// Append to the SaveActors TArray
			LocalSaveObject->MySavedActors.Add(ActorData);

			// artificial delay to simulate a heavy task.
			// this will block the game's main thread when using EAsyncExecution::TaskGraphMainThread
			FPlatformProcess::Sleep(0.5f);
		}
		
		// Once done, return to the Game Thread to save the game
		Async(EAsyncExecution::TaskGraphMainThread, [WeakThis, LocalSaveObject, SaveSlotName]()
		{
			if (!WeakThis.IsValid()) return;
		
			UMySaveGameAsyncSubsystem* ValidThis = WeakThis.Get();
		
			FAsyncSaveGameToSlotDelegate SaveGameCallbackDelegate;
			SaveGameCallbackDelegate.BindUObject(ValidThis, &UMySaveGameAsyncSubsystem::SaveGameAsyncCallback);
		
			UGameplayStatics::AsyncSaveGameToSlot(LocalSaveObject, SaveSlotName, 0, SaveGameCallbackDelegate);
		});
	});
}

void UMySaveGameAsyncSubsystem::LoadGameAsyncCallback(const FString& SlotName, int32 UserIndex, USaveGame* SaveGame)
{
	MySaveGameObject = Cast<UMySaveGameAsync>(SaveGame);
	
	if (MySaveGameObject != nullptr)
	{
		TArray<AActor*> SaveGameActors;
		UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UMySaveGameAsyncInterface::StaticClass(), SaveGameActors);
		TObjectPtr<UMySaveGameAsync> LocalSaveObject = MySaveGameObject;

		Async(EAsyncExecution::Thread, [LocalSaveObject, SaveGameActors]()
		{
			for (AActor* Actor : SaveGameActors)
			{
				for (FMyActorSaveAsyncData ActorData : LocalSaveObject->MySavedActors)
				{
					if (ActorData.Name == Actor->GetFName())
					{
						if (GEngine)
						{
							GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, *FString::Printf(TEXT("Actor Name: %s"), *Actor->GetFName().ToString()));
							GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, *FString::Printf(TEXT("Actor Transform: %s"), *ActorData.Transform.ToString()));
						}
						Actor->SetActorTransform(ActorData.Transform);

						// Use FMemoryReader to archive data
						FMemoryReader MyMemoryReader(ActorData.ByteData);
		
						FObjectAndNameAsStringProxyArchive Ar(MyMemoryReader, true);
						Ar.ArIsSaveGame = true;
						
						Actor->Serialize(Ar);
		
						IMySaveGameAsyncInterface::Execute_OnLoadGameAsync(Actor);
		
						break;
					}
				}
			}
		});
	}
}

void UMySaveGameAsyncSubsystem::SaveGameAsyncCallback(const FString& SlotName, int32 UserIndex, bool bSuccess)
{
	bSaving = false;
	// broadcast event to all listeners
	OnSavingGameAsync.Broadcast(SlotName, UserIndex, bSuccess, bSaving);
}
