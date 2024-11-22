#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActorTimer.generated.h"

class UBoxComponent;

UCLASS()
class MYPROJECT_API AMyActorTimer : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMyActorTimer();

	UPROPERTY(EditAnywhere)
	USceneComponent* Root;

	UPROPERTY(EditAnywhere)
	UBoxComponent* Box;

	UPROPERTY(EditAnywhere)
	FTimerHandle TimerHandle;

	UFUNCTION(BlueprintCallable)
	void StartTimer();

	UFUNCTION(BlueprintCallable)
	void StopTimer();

	UFUNCTION(BlueprintCallable)
	void TimerFunction();

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
