#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SaveGameSubsystem.generated.h"

class UMySaveGame;

/**
 * 
 */
UCLASS()
class MYPROJECT_API USaveGameSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FString SaveSlotName;

	UPROPERTY()
	TObjectPtr<UMySaveGame> CurrentSaveGame;
	
	UFUNCTION(BlueprintCallable)
	void SaveGame();

	UFUNCTION(BlueprintCallable)
	void LoadGame();

	UFUNCTION(BlueprintCallable)
	void ResetData();

	/* Initialize Subsystem, good moment to load in SaveGameSettings variables */
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
};
