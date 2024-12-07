#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SaveGameTriggerSphere.generated.h"

class USphereComponent;
class UTextRenderComponent;

UCLASS()
class MYPROJECT_API ASaveGameTriggerSphere : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASaveGameTriggerSphere();

	UPROPERTY(EditAnywhere)
	USceneComponent* Root;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	UTextRenderComponent* Text;

	UPROPERTY(EditAnywhere)
	USphereComponent* Sphere;

	UPROPERTY(EditAnywhere)
	bool bSaveGame;

	UPROPERTY(EditAnywhere)
	bool bLoadGame;

	UPROPERTY(EditAnywhere)
	bool bResetData;

	UFUNCTION()
	void LoadGame();

	UFUNCTION()
	void ResetData();
	
	UFUNCTION()
	void SaveGame();

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
