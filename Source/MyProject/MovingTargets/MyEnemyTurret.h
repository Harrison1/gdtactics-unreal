#pragma once

#include "CoreMinimal.h"
#include "MyMovingTargetInterface.h"
#include "GameFramework/Actor.h"
#include "MyEnemyTurret.generated.h"

class AMyMovingCharacter;
class AMyTurretProjectile;

UCLASS()
class MYPROJECT_API AMyEnemyTurret : public AActor, public IMyMovingTargetInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMyEnemyTurret();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual void ToggleActivation_Implementation() override;

	UPROPERTY()
	FTimerHandle ActivateTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	ACharacter* MyMovingCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	TSubclassOf<class AMyTurretProjectile> MyTurretProjectileClass;

	UFUNCTION()
	void ShootProjectile(float ProjectileSpeed);
};
