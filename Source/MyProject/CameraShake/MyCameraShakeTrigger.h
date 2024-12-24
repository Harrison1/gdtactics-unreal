#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyCameraShakeTrigger.generated.h"

class UBoxComponent;

UCLASS()
class MYPROJECT_API AMyCameraShakeTrigger : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMyCameraShakeTrigger();

	UPROPERTY(EditAnywhere)
	USceneComponent* MyRoot;

	UPROPERTY(EditAnywhere)
	UBoxComponent* MyBoxComponent;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};