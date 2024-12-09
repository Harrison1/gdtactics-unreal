/* Work in Progress */

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
		MySaveGame->SavedActors.Add(ActorData);
	}

	FAsyncSaveGameToSlotDelegate SaveGameCallbackDelegate;
	SaveGameCallbackDelegate.BindUObject(this, &UMySaveGameAsyncSubsystem::SaveGameCompleteCallback);

	UGameplayStatics::AsyncSaveGameToSlot(MySaveGame, MySlotName, 0, SaveGameCallbackDelegate);
}

void UMySaveGameAsyncSubsystem::SaveGameCompleteCallback(const FString& SlotName, int32 UserIndex, bool bSuccess)
{
	// broadcast event to all listeners
	OnSaveComplete.Broadcast(SlotName, UserIndex, bSuccess);
}