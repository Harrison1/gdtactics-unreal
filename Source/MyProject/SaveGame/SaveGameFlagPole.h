// Copyright HM Interactive, LLC. All Rights Reserved..

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SaveGameInterface.h"
#include "SaveGameFlagPole.generated.h"

class USphereComponent;

UCLASS()
class MYPROJECT_API ASaveGameFlagPole : public AActor, public ISaveGameInterface
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	// Sets default values for this actor's properties
	ASaveGameFlagPole();

	// Interface implementations
	virtual void OnLoadGame_Implementation() override;
	virtual void OnResetData_Implementation() override;

	UPROPERTY(EditAnywhere)
	USceneComponent* Root;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* FlagMesh;

	UPROPERTY(EditAnywhere)
	USphereComponent* Sphere;

	UPROPERTY(EditAnywhere, SaveGame)
	bool bActive;
	
	UPROPERTY(EditAnywhere)
	FVector FlagOriginLocation;

	UPROPERTY(EditAnywhere)
	FVector TargetLocation;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
