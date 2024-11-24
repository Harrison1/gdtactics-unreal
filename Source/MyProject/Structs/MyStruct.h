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
	FString Name;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Health;

	// Constructor
	FMyStruct() : Name(TEXT("Default")), Health(100) {}
};
