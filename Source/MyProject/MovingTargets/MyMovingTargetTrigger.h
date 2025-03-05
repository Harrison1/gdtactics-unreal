#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyMovingTargetTrigger.generated.h"

class UBoxComponent;

UCLASS()
class MYPROJECT_API AMyMovingTargetTrigger : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMyMovingTargetTrigger();
	
	UPROPERTY()
	USceneComponent* Root;

	UPROPERTY(EditAnywhere)
	UBoxComponent* TriggerBox;

	UFUNCTION()
	void TriggerInterfaceAction();
	
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
