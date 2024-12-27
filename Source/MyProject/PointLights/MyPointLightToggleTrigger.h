#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyPointLightToggleTrigger.generated.h"

class AMyPointLight;
class UBoxComponent;
class UTextRenderComponent;


UCLASS()
class MYPROJECT_API AMyPointLightToggleTrigger : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMyPointLightToggleTrigger();

	UPROPERTY(EditAnywhere)
	USceneComponent* MyRoot;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MyStaticMesh;

	UPROPERTY(EditAnywhere)
	UBoxComponent* MyBoxComponent;

	UPROPERTY(EditAnywhere)
	UTextRenderComponent* MyTextRenderComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AMyPointLight*> MyPointLights;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
