#include "MySaveGameAsyncSubsystem.h"
#include "MySaveGameAsync.h"
#include "MySaveGameAsyncInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"

void UMySaveGameAsyncSubsystem::SaveGameAsync()
{
	// start with an empty file
	MySaveGame->SavedActors.Empty();
	
	TArray<AActor*> SaveGameActors;
	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UMySaveGameAsyncInterface::StaticClass(), SaveGameActors);

	for (AActor* Actor : SaveGameActors)
	{
		FActorSaveData ActorData;
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
		MySaveGame->SavedActors.Add(ActorData);
	}

	UGameplayStatics::AsyncSaveGameToSlot(MySaveGame, MySlotName, 0);
}
