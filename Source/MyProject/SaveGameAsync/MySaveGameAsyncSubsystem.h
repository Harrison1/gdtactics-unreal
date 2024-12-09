#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MySaveGameAsyncSubsystem.generated.h"

class UMySaveGameAsync;


UCLASS()
class MYPROJECT_API UMySaveGameAsyncSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FString MySlotName;

	UPROPERTY()
	TObjectPtr<UMySaveGameAsync> MySaveGame;
	
	UFUNCTION(BlueprintCallable)
	void SaveGameAsync();

	UFUNCTION(BlueprintCallable)
	void LoadGameAsync();

	UFUNCTION(BlueprintCallable)
	void ResetGameAsync();
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
};
