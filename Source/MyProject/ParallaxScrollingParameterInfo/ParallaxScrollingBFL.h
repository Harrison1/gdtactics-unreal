#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ParallaxScrollingBFL.generated.h"

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
class MYPROJECT_API UParallaxScrollingBFL : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "Materials")
	static TArray<FMyParallaxStruct> CreateLayerOffsetArray(UMaterialInstanceDynamic* MaterialInstanceDynamic, float OffsetTime);
};
