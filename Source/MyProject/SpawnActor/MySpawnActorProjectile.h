#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MySpawnActorProjectile.generated.h"

class UBoxComponent;
class UProjectileMovementComponent;

UCLASS()
class MYPROJECT_API AMySpawnActorProjectile : public AActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	// Sets default values for this actor's properties
	AMySpawnActorProjectile();

	UPROPERTY(EditAnywhere)
	UBoxComponent* MyCollisionComp;

	UPROPERTY(EditAnywhere)
	UProjectileMovementComponent* MyMovementComp;

	UFUNCTION()
	void Accelerate();
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
