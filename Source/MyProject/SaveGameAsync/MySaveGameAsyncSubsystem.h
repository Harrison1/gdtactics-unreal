#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MySaveGameAsyncSubsystem.generated.h"

class UMySaveGameAsync;
class USaveGame;

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
	bool bLoading = false;

	UPROPERTY()
	bool bSaving = false;

	UFUNCTION(BlueprintCallable)
	void DeleteAllAsyncSaveFiles(FString File1, FString File2, FString File3);
	
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
