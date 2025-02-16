#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyWeapon.generated.h"

class UDataTable;
class USkeletalMeshComponent;
class UTextRenderComponent;

UCLASS()
class MYPROJECT_API AMyWeapon : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMyWeapon();

	virtual void OnConstruction(const FTransform& Transform) override;

	UPROPERTY(EditAnywhere)
	USceneComponent* MySceneComponent;
	
	UPROPERTY(EditAnywhere)
	UTextRenderComponent* MyWeaponNameText;

	UPROPERTY(EditAnywhere)
	UTextRenderComponent* MyWeaponDamangeText;

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* MySkeletalMesh;
	
	UPROPERTY(EditAnywhere)
	UDataTable* MyDataTable;

	UPROPERTY(EditAnywhere)
	int32 MyIndex;

	UPROPERTY(EditAnywhere)
	UMaterialInstanceDynamic* DynamicMaterial;

	UFUNCTION(BlueprintCallable)
	void SetGun();
};
