#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyPointLight.generated.h"

class UPointLightComponent;

UCLASS()
class MYPROJECT_API AMyPointLight : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMyPointLight();
	
	UPROPERTY(EditAnywhere)
	USceneComponent* MyRoot;

	UPROPERTY(EditAnywhere)
	UPointLightComponent* MyPointLight;

	UPROPERTY()
	FTimerHandle TimerHandle;
	
	UFUNCTION()
	void ToggleTimer();

	void SetRandomColor();
};
