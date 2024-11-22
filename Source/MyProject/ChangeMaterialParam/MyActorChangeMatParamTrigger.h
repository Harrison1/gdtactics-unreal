#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActorChangeMatParamTrigger.generated.h"

class UBoxComponent;
class AMyActorChangeMatParam;

UCLASS()
class MYPROJECT_API AMyActorChangeMatParamTrigger : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMyActorChangeMatParamTrigger();

	UPROPERTY(EditAnywhere)
	USceneComponent* Root;

	UPROPERTY(EditAnywhere)
	UBoxComponent* Box;

	UPROPERTY(EditAnywhere)
	TArray<AMyActorChangeMatParam*> MyMatActors;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void RandomizeParams();
};
