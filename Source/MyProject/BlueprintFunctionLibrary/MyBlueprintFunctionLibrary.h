#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyBlueprintFunctionLibrary.generated.h"

UCLASS()
class MYPROJECT_API UMyBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	// Static functions do not require a target and they will appear in blueprints when Context Sensitive is checked
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Door Functions")
	static bool IsActorInFront(FVector ActorLocation, FVector OtherActorLocation, FRotator OtherActorRotation);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Door Functions")
	static FRotator GetRotateValue(FRotator ActorRotation, float Alpha, bool OpenDirection, float RotateDegrees);
};
