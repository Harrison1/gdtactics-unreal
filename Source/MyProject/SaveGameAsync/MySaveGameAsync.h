#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MySaveGameAsync.generated.h"


USTRUCT()
struct FMyActorSaveAsyncData
{
	GENERATED_BODY()

	UPROPERTY()
	FName Name;

	UPROPERTY()
	FTransform Transform;

	UPROPERTY()
	FDateTime DateTime;

	UPROPERTY()
	TArray<uint8> ByteData;
};

UCLASS()
class MYPROJECT_API UMySaveGameAsync : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TArray<FMyActorSaveAsyncData> MySavedActors;
};
