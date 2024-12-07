#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SaveGameInterface.h"
#include "SaveGameCoin.generated.h"

class USphereComponent;

UCLASS()
class MYPROJECT_API ASaveGameCoin : public AActor, public ISaveGameInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASaveGameCoin();

	// Interface implementations
	virtual void OnLoadGame_Implementation() override;
	virtual void OnResetData_Implementation() override;

	UPROPERTY()
	int32 UUID;

	UPROPERTY(EditAnywhere)
	USceneComponent* Root;
	
	UPROPERTY(EditAnywhere)
	USphereComponent* Sphere;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, SaveGame)
	bool bActive = true;

	UFUNCTION()
	void Activate();

	UFUNCTION()
	void Deactivate();

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
