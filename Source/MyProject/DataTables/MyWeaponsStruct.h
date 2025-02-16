#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MyWeaponsStruct.generated.h"


USTRUCT()
struct FMyWeaponsStruct : public FTableRowBase
{
	GENERATED_BODY()

	/** Name of Gun */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Weapons)
	FString Name;

	/** Gun Skeletal Mesh*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Weapons)
	USkeletalMesh* SkeletalMesh;

	/** Material Color */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Weapons)
	FLinearColor Color;
	
	/** Damage */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Weapons)
	float Damage;
	
	/** Bullet Range */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Weapons)
	float Range;
	
	/** Fire Rate per Minute */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Weapons)
	float RPM;
	
	/** Magazine / Clip Capacity */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Weapons)
	float Magazine;
	
	/** How Long to Reload */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Weapons)
	float Reload;
};
