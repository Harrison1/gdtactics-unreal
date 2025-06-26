#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PrototypeInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UPrototypeInterface : public UInterface
{
	GENERATED_BODY()
};

class MYPROJECT_API IPrototypeInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PrototypeInterface")
	void Interact();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PrototypeInterface")
	void StopInteract();
};
