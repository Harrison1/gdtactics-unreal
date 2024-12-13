#include "MySaveGameAsyncSubsystem.h"
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
	// else
	// {
	// 	MySaveGameObject = CastChecked<UMySaveGameAsync>(UGameplayStatics::CreateSaveGameObject(UMySaveGameAsync::StaticClass()));
	// }
}

void UMySaveGameAsyncSubsystem::SaveGameAsync()
{
	TObjectPtr<UMySaveGameAsync> LocalSaveObject = CastChecked<UMySaveGameAsync>(UGameplayStatics::CreateSaveGameObject(UMySaveGameAsync::StaticClass()));
	
	if (!IsValid(LocalSaveObject) || bSaving) return;
	
	bSaving = true;

	// broadcast to listeners that we're saving the game
	OnSavingGameAsync.Broadcast(MySlotName, 0, false, bSaving);

	// create a local instance of variables to be captured and used in the lambda
	TWeakObjectPtr<UMySaveGameAsyncSubsystem> WeakThis = this; // Alternatively: auto WeakThis = TWeakObjectPtr(this);
	UWorld* World = GetWorld();
	// TObjectPtr<UMySaveGameAsync> LocalSaveObject = MySaveGameObject;
	FString SaveSlotName = MySlotName;

	// if you want to get all the actors inside the Async task or use TActorRange you'll have
	// to run the operation on the main thread with EAsyncExecution::TaskGraphMainThread
	TArray<AActor*> SaveGameActors;
	UGameplayStatics::GetAllActorsWithInterface(World, UMySaveGameAsyncInterface::StaticClass(), SaveGameActors);
	
	Async(EAsyncExecution::Thread, [WeakThis, LocalSaveObject, SaveSlotName, SaveGameActors]()
	{
		// clear out content
		// LocalSaveObject->MySavedActors.Empty();
		
		// Alternative: for (AActor* Actor : TActorRange<AActor>(World)) then check if Actor->Implements<UMySaveGameAsyncInterface>(),
		// but since we're inside an Async operation you'll need to use EAsyncExecution::TaskGraphMainThread for TActorRange to work
		for (AActor* Actor : SaveGameActors)
		{
			FMyActorSaveAsyncData ActorData;
			ActorData.Name = Actor->GetFName();
			ActorData.Transform = Actor->GetActorTransform();
			
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

			/** FPlatformProcess::Sleep is here to purposely delay the events and artificially simulate a heavy task for testing.
			* Note: this will block the game's main thread when using EAsyncExecution::TaskGraphMainThread
			* Uncomment when not needed
			*/
			FPlatformProcess::Sleep(0.1f);
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
	
	// MySaveGameObject = Cast<UMySaveGameAsync>(SaveGame);
	TObjectPtr<UMySaveGameAsync> LocalSaveObject = Cast<UMySaveGameAsync>(SaveGame);
	
	if (!IsValid(LocalSaveObject)) return;
	
	TArray<AActor*> SaveGameActors;
	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UMySaveGameAsyncInterface::StaticClass(), SaveGameActors);
	// TObjectPtr<UMySaveGameAsync> LocalSaveObject = MySaveGameObject;

	// Begin the Async operation in an outside thread.
	Async(EAsyncExecution::Thread, [LocalSaveObject, SaveGameActors]()
	{
		TArray<TPair<AActor*, FMyActorSaveAsyncData>> ProcessedActors;

		for (AActor* Actor : SaveGameActors)
		{
			if (!IsValid(Actor)) continue;

			for (const FMyActorSaveAsyncData& ActorData : LocalSaveObject->MySavedActors)
			{
				if (ActorData.Name == Actor->GetFName())
				{
					ProcessedActors.Add(TPair<AActor*, FMyActorSaveAsyncData>(Actor, ActorData));
					break;
				}
			}
		}

		// Being the Async operation in the GameThread. Since we're updating game world actors we need the game thread
		AsyncTask(ENamedThreads::GameThread, [ProcessedActors]()
		{
			constexpr int32 BatchSize = 5;
			static int32 CurrentIndex = 0;

			static FTimerHandle TimerHandle;

			/** Delegate function that updates back to the game thread incrementally
			* When doing this in batches every frame will allow us not permanently block the main thread
			* We could put a loading screen with this technique and limit interruptions.
			*/  
			FTimerDelegate TimerDel;
			TimerDel.BindLambda([ProcessedActors]() mutable
			{
				for (int32 i = 0; i < BatchSize && CurrentIndex < ProcessedActors.Num(); ++i, ++CurrentIndex)
				{
					const auto& Pair = ProcessedActors[CurrentIndex];
					AActor* Actor = Pair.Key;
					const FMyActorSaveAsyncData& ActorData = Pair.Value;

					if (IsValid(Actor))
					{
						Actor->SetActorTransform(ActorData.Transform);

						FMemoryReader MyMemoryReader(ActorData.ByteData);
						FObjectAndNameAsStringProxyArchive Ar(MyMemoryReader, true);
						Ar.ArIsSaveGame = true;

						Actor->Serialize(Ar);

						// Execute an interface call if you want an actor to perform logic when laoded
						// currently I don't have any actore listening for this event
						IMySaveGameAsyncInterface::Execute_OnLoadGameAsync(Actor);
					}
				}

				// Stop the timer when all actors are processed
				if (CurrentIndex >= ProcessedActors.Num())
				{
					// UWorld* World = GEngine->GetWorldFromContextObjectChecked(ProcessedActors[0].Key);
					if (UWorld* World = GEngine->GetWorldFromContextObjectChecked(ProcessedActors[0].Key))
					{
						World->GetTimerManager().ClearTimer(TimerHandle);
					}

					if (GEngine)
					{
						GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("All Actors Have Been loaded"));
					}
				}
			});

			// Start a timer that runs every 0.1s that calls the binded delegate function to process all the saved actors in batches
			// UWorld* World = GEngine->GetWorldFromContextObjectChecked(ProcessedActors[0].Key);
			if (UWorld* World = GEngine->GetWorldFromContextObjectChecked(ProcessedActors[0].Key))
			{
				World->GetTimerManager().SetTimer(TimerHandle, TimerDel, 0.1f, true);
			}
		});
	});
}

void UMySaveGameAsyncSubsystem::SaveGameAsyncCallback(const FString& SlotName, int32 UserIndex, bool bSuccess)
{
	bSaving = false;
	// broadcast event to all listeners
	OnSavingGameAsync.Broadcast(SlotName, UserIndex, bSuccess, bSaving);
}
