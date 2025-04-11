#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActorCPD.generated.h"

UCLASS()
class MYPROJECT_API AMyActorCPD : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMyActorCPD();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY()
	FTimerHandle TimerHandle;

	UFUNCTION(BlueprintCallable)
	void StartTimer();

	UFUNCTION(BlueprintCallable)
	void StopTimer();

	UFUNCTION()
	void TimerFunction() const;
};
