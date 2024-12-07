#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MySaveGame.generated.h"

USTRUCT()
struct FActorSaveData
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FName ActorName;

	UPROPERTY()
	FTransform ActorTransform;

	UPROPERTY()
	TArray<uint8> ByteData;
};

UCLASS()
class MYPROJECT_API UMySaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TArray<FActorSaveData> SavedActors;
};
