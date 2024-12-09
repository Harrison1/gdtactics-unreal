#include "MySaveGameAsyncSubsystem.h"
#include "MySaveGameAsync.h"
#include "MySaveGameAsyncInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"

void UMySaveGameAsyncSubsystem::SaveGameAsync()
{
	// start with an empty file
	SaveGame->SavedActors.Empty();
	
	TArray<AActor*> SaveGameActors;
	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UMySaveGameAsyncInterface::StaticClass(), SaveGameActors);

	for (AActor* Actor : SaveGameActors)
	{
		FActorSaveData ActorData;
		ActorData.Name = Actor->GetFName();
		ActorData.Transform = Actor->GetActorTransform();
		
		// Write the data to a memory writer
		FMemoryWriter MyMemoryWriter(ActorData.ByteData);
	
		FObjectAndNameAsStringProxyArchive Ar(MyMemoryWriter, true);

		// set this archive saving/loading state to true and then serialize to binary data
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

// void USaveGameSubsystem::LoadGame()
// {
// 	if (UGameplayStatics::DoesSaveGameExist(SaveSlotName, 0))
// 	{
// 		CurrentSaveGame = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0));
//
// 		TArray<AActor*> SaveGameActors;
// 		UGameplayStatics::GetAllActorsWithInterface(GetWorld(), USaveGameInterface::StaticClass(), SaveGameActors);
//
// 		for (AActor* Actor : SaveGameActors)
// 		{
// 			for (FActorSaveData ActorData : CurrentSaveGame->SavedActors)
// 			{
// 				if (ActorData.ActorName == Actor->GetFName())
// 				{
// 					// set the actor trasform here if you set it in the save function
// 					// Actor->SetActorTransform(ActorData.ActorTransform);
//
// 					// We follow the same process as the save function but replace FMemoryWriter with FMemoryReader
// 					// to get the binary back to Actor variable values
// 					FMemoryReader MyMemoryReader(ActorData.ByteData);
// 	
// 					FObjectAndNameAsStringProxyArchive Ar(MyMemoryReader, true);
// 					Ar.ArIsSaveGame = true;
// 					
// 					Actor->Serialize(Ar);
// 	
// 					ISaveGameInterface::Execute_OnLoadGame(Actor);
// 	
// 					break;
// 				}
// 			}
// 		}
//
// 		if (GEngine)
// 		{
// 			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Load Game Successful!"));
// 		}
// 	}
// }
//
// void USaveGameSubsystem::ResetData()
// {
// 	TArray<AActor*> SaveGameActors;
// 	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), USaveGameInterface::StaticClass(), SaveGameActors);
//
// 	for (AActor* Actor : SaveGameActors)
// 	{
// 		ISaveGameInterface::Execute_OnResetData(Actor);
// 	}
//
// 	CurrentSaveGame->SavedActors.Empty();
// 	
// 	UGameplayStatics::SaveGameToSlot(CurrentSaveGame, SaveSlotName, 0);
// 	
// 	if (GEngine)
// 	{
// 		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Data Reset Successful!"));
// 	}
// }
