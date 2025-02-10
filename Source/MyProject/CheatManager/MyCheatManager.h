#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CheatManager.h"
#include "MyCheatManager.generated.h"

UCLASS()
class MYPROJECT_API UMyCheatManager : public UCheatManager
{
	GENERATED_BODY()

	UFUNCTION(Exec)
	void GetPlayerName();
};
