#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MySaveGameAsyncSubsystem.generated.h"

class UMySaveGameAsync;
class USaveGame;

// declare a delegate to use and broadcast after the async save function has completed
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FSaveCompleteDelegate, const FString&, SlotName, int32, UserIndex, bool, bSuccess, bool, bSaving);

UCLASS()
class MYPROJECT_API UMySaveGameAsyncSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	// Multicast delegate for save completion
	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "Save System")
	FSaveCompleteDelegate OnSavingGameAsync;
	
	UPROPERTY()
	FString MySlotName;

	UPROPERTY()
	bool bSaving = false;

	// UPROPERTY()
	// TObjectPtr<UMySaveGameAsync> MySaveGameObject;
	
	UFUNCTION(BlueprintCallable)
	void SaveGameAsync();

	UFUNCTION(BlueprintCallable)
	void LoadGameAsync(FString LoadSlotName);
private:
	// Callback to call the broadcast event when saving completes
	void SaveGameAsyncCallback(const FString& SlotName, int32 UserIndex, bool bSuccess);

	// Load Game Async Callback
	void LoadGameAsyncCallback(const FString& SlotName, int32 UserIndex, USaveGame* SaveGame);
};
