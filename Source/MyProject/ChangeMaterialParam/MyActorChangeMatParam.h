#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyProject/Prototype/PrototypeInterface.h"
#include "MyActorChangeMatParam.generated.h"

UCLASS()
class MYPROJECT_API AMyActorChangeMatParam : public AActor, public IPrototypeInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMyActorChangeMatParam();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere)
	USceneComponent* Root;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere)
	UMaterialInstanceDynamic* DynamicMaterial;

	UPROPERTY(EditAnywhere)
	FName VectorParamName = FName("Color");

	UPROPERTY(EditAnywhere)
	FName ScalarParamName = FName("Emissive");

	UFUNCTION(BlueprintCallable)
	void UpdateMaterial(FVector Color = FVector(1.f, 1.f, 1.f), float Emissive = 0.f, bool Randomize = true);

	UPROPERTY()
	FTimerHandle TimerHandle;

	UFUNCTION(BlueprintCallable)
	void StartTimer();

	void Interact_Implementation() override;
	void StopInteract_Implementation() override;
};
