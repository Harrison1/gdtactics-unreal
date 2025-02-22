#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyPluginBFLibrary.generated.h"


UCLASS()
class UMyPluginBFLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "Get Distance to Actor in Front", Keywords = "Get Distance to Actor in Front"), Category = "MyPlugin")
	static float GetDistanceToActorInFront(AActor* MyActor, const float TraceLength = 50000.f);
};
