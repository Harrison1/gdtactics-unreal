#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MySpawnActorInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UMySpawnActorInterface : public UInterface
{
	GENERATED_BODY()
};


class MYPROJECT_API IMySpawnActorInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MySpawnActorInterface")
	void SpawnActor();
};