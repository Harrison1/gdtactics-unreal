/* Work in Progress */

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MySaveGameAsyncInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UMySaveGameAsyncInterface : public UInterface
{
	GENERATED_BODY()
};


class MYPROJECT_API IMySaveGameAsyncInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent)
	void OnLoadGameAsync();

	UFUNCTION(BlueprintNativeEvent)
	void OnSaveGameAsync();
};
