#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "MyWidget_ListEntry.generated.h"

class UCanvasPanel;
class UImage;
class UProgressBar;
class UTextBlock;


UCLASS()
class MYPROJECT_API UMyWidget_ListEntry : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

public:
	void OnListItemObjectSet_Implementation(UObject* ListItemObject);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UCanvasPanel* Panel;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* Image;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* Name;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* HealthBar;

	UFUNCTION(BlueprintCallable)
	void SetHealth(float NewHealth);

	UFUNCTION(BlueprintCallable)
	void SetName(FString NewName);
};
