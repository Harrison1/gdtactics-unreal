#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyDelegateActorTrigger.generated.h"

class UBoxComponent;
class UTextRenderComponent;

UCLASS()
class MYPROJECT_API AMyDelegateActorTrigger : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMyDelegateActorTrigger();

	UPROPERTY(EditAnywhere)
	USceneComponent* DefaultSceneRoot;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MyMesh;

	UPROPERTY(EditAnywhere)
	UBoxComponent* MyBox;

	UPROPERTY(EditAnywhere)
	UTextRenderComponent* MyText;
	
	UPROPERTY(EditAnywhere)
	float ManaValue = -10.0f;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
