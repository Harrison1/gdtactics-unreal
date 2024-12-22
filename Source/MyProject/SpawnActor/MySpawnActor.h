#pragma once

#include "CoreMinimal.h"
#include "MySpawnActorInterface.h"
#include "GameFramework/Actor.h"
#include "MySpawnActor.generated.h"

class AMySpawnActorParticle;
class AMySpawnActorPhysics;
class AMySpawnActorProjectile;

UCLASS()
class MYPROJECT_API AMySpawnActor : public AActor, public IMySpawnActorInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMySpawnActor();

	UPROPERTY()
	USceneComponent* Root;

	UPROPERTY(EditAnywhere)
	bool bSpawnPhysicsActor;

	UPROPERTY(EditAnywhere);
	bool bSpawnProjectileActor;

	UPROPERTY(EditAnywhere)
	bool bSpawnParticleEffect;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AMySpawnActorPhysics> MySpawnActorPhysicsClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AMySpawnActorProjectile> MySpawnActorProjectileClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AMySpawnActorParticle> MySpawnActorParticleClass;
	
	UFUNCTION()
	void SpawnPhysicsActor();

	UFUNCTION()
	void SpawnProjectileActor();

	UFUNCTION()
	void SpawnParticleEffect();

	UFUNCTION()
	FVector RandomColor();

	void SpawnActor_Implementation() override;
};
