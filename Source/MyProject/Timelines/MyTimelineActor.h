#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyTimelineActor.generated.h"

class UCurveFloat;
class UTimelineComponent;

UCLASS()
class MYPROJECT_API AMyTimelineActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMyTimelineActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere)
	FVector StartLocation;
	
	UPROPERTY(EditAnywhere)
	FVector EndLocation;

	UPROPERTY(EditAnywhere)
	UCurveFloat* AlphaCurve;
	
	UPROPERTY(EditAnywhere)
	UTimelineComponent* MyTimeline;

	UFUNCTION()
	void Update(float Value);
};
