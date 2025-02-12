#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CheatManager.h"
#include "MyCheatManager.generated.h"

UCLASS()
class MYPROJECT_API UMyCheatManager : public UCheatManager
{
	GENERATED_BODY()

	UMyCheatManager();

	UFUNCTION(Exec)
	void GetPlayerName();

	UFUNCTION()
	static void MyCommandFunction(const TArray<FString>& Args, UWorld* World);
};
