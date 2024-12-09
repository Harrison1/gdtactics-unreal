/* Work in Progress */

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MySaveGameAsyncSubsystem.generated.h"

class UMySaveGameAsync;

// declare a delegate to use and broadcast after the async save function has completed
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FSaveCompleteDelegate, const FString&, SlotName, int32, UserIndex, bool, bSuccess);

UCLASS()
class MYPROJECT_API UMySaveGameAsyncSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	// Multicast delegate for save completion
	UPROPERTY(BlueprintCallable, Category = "Save System")
	FSaveCompleteDelegate OnSaveComplete;
	
	UPROPERTY()
	FString MySlotName;

	UPROPERTY()
	TObjectPtr<UMySaveGameAsync> MySaveGameObject;
	
	UFUNCTION(BlueprintCallable)
	void SaveGameAsync();

	// UFUNCTION(BlueprintCallable)
	// void LoadGameAsync();
	//
	// UFUNCTION(BlueprintCallable)
	// void ResetGameAsync();
	//
	// virtual void Initialize(FSubsystemCollectionBase& Collection) override;

private:
	// Callback to call the broadcast event when saving completes
	void SaveGameCompleteCallback(const FString& SlotName, int32 UserIndex, bool bSuccess);
};
