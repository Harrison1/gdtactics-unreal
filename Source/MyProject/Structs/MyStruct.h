#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MyStruct.generated.h"

USTRUCT(BlueprintType, Blueprintable)
struct FMyStruct
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Health;

	// Constructor
	FMyStruct() : Name(FName("Default")), Health(100) {}
};
