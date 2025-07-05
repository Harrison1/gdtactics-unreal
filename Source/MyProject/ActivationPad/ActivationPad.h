#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActivationPad.generated.h"

class UBoxComponent;
class UNiagaraSystem;

UCLASS()
class MYPROJECT_API AActivationPad : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AActivationPad();
	
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Base;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Pad;

	UPROPERTY(EditAnywhere)
	UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere)
	TArray<AActor*> InterfaceActors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* PressureSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UNiagaraSystem* Steam;

	UFUNCTION(BlueprintCallable)
	void StartAction();

	UFUNCTION(BlueprintCallable)
	void StopAction();
};
