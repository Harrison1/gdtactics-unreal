#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SaveGameInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class USaveGameInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MYPROJECT_API ISaveGameInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// Load game data from save file
	UFUNCTION(BlueprintNativeEvent)
	void OnLoadGame();

	// Rest and save data to original state
	UFUNCTION(BlueprintNativeEvent)
	void OnResetData();
};
