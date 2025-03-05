#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GameFramework/DamageType.h"
#include "MyDamageTypes.generated.h"

UENUM(BlueprintType)
enum class EMyDamageTypes : uint8
{
	Gas		UMETA(DisplayName = "Gas"),
	Fire	UMETA(DisplayName = "Fire"),
	Water	UMETA(DisplayName = "Water")
};

UCLASS()
class MYPROJECT_API UGasDamageType : public UDamageType
{
	GENERATED_BODY()
};

UCLASS()
class MYPROJECT_API UFireDamageType : public UDamageType
{
	GENERATED_BODY()
};

UCLASS()
class MYPROJECT_API UWaterDamageType : public UDamageType
{
	GENERATED_BODY()
};

UCLASS()
class MYPROJECT_API UMyDamageTypes : public UObject
{
	GENERATED_BODY()

public:
	static TSubclassOf<UDamageType> GetDamageTypeClass(EMyDamageTypes DamageType);
};
