#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyInterface.h"
#include "MyInterfaceMovableActor.generated.h"

class UBillboardComponent;
class UCurveFloat;
class UTimelineComponent;

UCLASS()
class MYPROJECT_API AMyInterfaceMovableActor : public AActor, public IMyInterface
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AMyInterfaceMovableActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Blueprint Native Event override
	void PerformAction_Implementation() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default", meta = (AllowPrivateAccess = "true"))
	UBillboardComponent* DefaultSceneRoot;
	
	UPROPERTY(EditAnywhere);
	UStaticMeshComponent* MovableMesh;

	UPROPERTY(EditAnywhere)
	UCurveFloat* AlphaCurve;
	
	UTimelineComponent* MyTimeline;

	UFUNCTION()
	void MoveMesh(float Value);
};
