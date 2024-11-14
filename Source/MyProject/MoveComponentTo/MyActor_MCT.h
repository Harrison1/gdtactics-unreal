#pragma once

#include "CoreMinimal.h"
#include "MyActor_MCT.generated.h"

UCLASS()
class MYPROJECT_API AMyActor_MCT : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMyActor_MCT();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY()
	USceneComponent* Root;
	
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere)
	FVector TargetLocation;

	UPROPERTY(EditAnywhere)
	float OverTime = 4.f;

	UFUNCTION()
	void MoveToTarget();

	UFUNCTION()
	void ReturnToOrigin();

	FLatentActionInfo LatentInfo;
};
