#include "SaveGameSubsystem.h"
#include "MySaveGame.h"
#include "SaveGameInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"

void USaveGameSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	// For testing purposes I'm setting the SaveSlotName and CurrentSaveGame values here.
	SaveSlotName = TEXT("SaveGame01");
	
	if (UGameplayStatics::DoesSaveGameExist(SaveSlotName, 0))
	{
		CurrentSaveGame = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0));
	}
	else
	{
		CurrentSaveGame = CastChecked<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
	}
}

void USaveGameSubsystem::SaveGame()
{
	// start with an empty file
	CurrentSaveGame->SavedActors.Empty();
	
	TArray<AActor*> SaveGameActors;
	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), USaveGameInterface::StaticClass(), SaveGameActors);

	for (AActor* Actor : SaveGameActors)
	{
		FActorSaveData ActorData;
		ActorData.ActorName = Actor->GetFName();

		// set ActorTransform if you want ot save the location/rotation/scale of a physics actors or object
		// this simple example won't be using actor transform data.
		// ActorData.ActorTransform = Actor->GetActorTransform();
		
		FMemoryWriter MyMemoryWriter(ActorData.ByteData);
	
		FObjectAndNameAsStringProxyArchive Ar(MyMemoryWriter, true);

		Ar.ArIsSaveGame = true;
		Actor->Serialize(Ar);
	
		CurrentSaveGame->SavedActors.Add(ActorData);
	}

	UGameplayStatics::SaveGameToSlot(CurrentSaveGame, SaveSlotName, 0);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Save Game Successful"));
	}
}

void USaveGameSubsystem::LoadGame()
{
	if (UGameplayStatics::DoesSaveGameExist(SaveSlotName, 0))
	{
		CurrentSaveGame = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0));

		TArray<AActor*> SaveGameActors;
		UGameplayStatics::GetAllActorsWithInterface(GetWorld(), USaveGameInterface::StaticClass(), SaveGameActors);

		for (AActor* Actor : SaveGameActors)
		{
			for (FActorSaveData ActorData : CurrentSaveGame->SavedActors)
			{
				if (ActorData.ActorName == Actor->GetFName())
				{
					// set the actor trasform here if you set it in the save function
					// Actor->SetActorTransform(ActorData.ActorTransform);

					// We follow the same process as the save function but replace FMemoryWriter with FMemoryReader
					// to get the binary back to Actor variable values
					FMemoryReader MyMemoryReader(ActorData.ByteData);
	
					FObjectAndNameAsStringProxyArchive Ar(MyMemoryReader, true);
					Ar.ArIsSaveGame = true;
					
					Actor->Serialize(Ar);
	
					ISaveGameInterface::Execute_OnLoadGame(Actor);
	
					break;
				}
			}
		}

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Load Game Successful!"));
		}
	}
}

void USaveGameSubsystem::ResetData()
{
	TArray<AActor*> SaveGameActors;
	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), USaveGameInterface::StaticClass(), SaveGameActors);

	for (AActor* Actor : SaveGameActors)
	{
		ISaveGameInterface::Execute_OnResetData(Actor);
	}

	CurrentSaveGame->SavedActors.Empty();
	
	UGameplayStatics::SaveGameToSlot(CurrentSaveGame, SaveSlotName, 0);
	
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Data Reset Successful!"));
	}
}
