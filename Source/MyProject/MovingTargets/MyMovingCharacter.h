#pragma once

#include "CoreMinimal.h"
#include "MyMovingTargetInterface.h"
#include "GameFramework/Character.h"
#include "MyMovingCharacter.generated.h"

UCLASS()
class MYPROJECT_API AMyMovingCharacter : public ACharacter, public IMyMovingTargetInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyMovingCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Interface Activation
	virtual void ToggleActivation_Implementation() override;
	
	bool bActive = false;
	float Health = 50.f;
	FTransform Origin;
	void Activate();
	void Deactivate();

	UPROPERTY()
	FTransform SpawnPoint;

	UPROPERTY(EditAnywhere)
	FTimerHandle SpawnTimerHandle;
	
	UPROPERTY(EditAnywhere)
	TArray<AActor*> SpawnPoints;

	UFUNCTION()
	void SpawnActor();
	
	UFUNCTION()
	void ProcessDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
};
