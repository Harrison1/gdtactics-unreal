#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MySpawnActorTrigger.generated.h"

class UBoxComponent;

UCLASS()
class MYPROJECT_API AMySpawnActorTrigger : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMySpawnActorTrigger();

	UPROPERTY(EditAnywhere)
	USceneComponent* MyRoot;

	UPROPERTY(EditAnywhere)
	UBoxComponent* MyBoxComponent;

	UPROPERTY(EditAnywhere)
	AActor* MySpawnedActor;

	int32 SpawnCounter = 0;
	int32 MaxSpawnCount = 10; // Stop spawning actors after 10 have spawned for testing

	UPROPERTY()
	FTimerHandle TimerHandle;

	UFUNCTION(BlueprintCallable)
	void StartTimer();

	UFUNCTION(BlueprintCallable)
	void MyTimerFunction();

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
