#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyStructBoundingBox.generated.h"

class UBoxComponent;
class UMyWidget_List;

UCLASS()
class MYPROJECT_API AMyStructBoundingBox : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMyStructBoundingBox();
	
	UPROPERTY(EditAnywhere)
	USceneComponent* Root;

	UPROPERTY(EditAnywhere)
	UBoxComponent* Box;

	UFUNCTION(BLueprintCallable)
	TArray<AActor*> GetPlayers();
};
