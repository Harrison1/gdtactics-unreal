// Unreal Engine 5.2.1

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyBlueprintFunctionLibrary.generated.h"

USTRUCT(BlueprintType)
struct FMyParallaxStruct
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName LayerName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float OffsetValue;
};

UCLASS()
class PROJECTDDS_API UMyBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "Materials")
	static TArray<FMyParallaxStruct> CreateLayerOffsetArray(UMaterialInstanceDynamic* MaterialInstanceDynamic, float OffsetTime);
};
