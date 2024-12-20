#include "MyWidget_ListEntry.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "MyProject/Structs/MyStructPlayer.h"

void UMyWidget_ListEntry::SetHealth(float NewHealth)
{
	float NewHealthPct = NewHealth / 100.f;

	HealthBar->SetPercent(NewHealthPct);
}

void UMyWidget_ListEntry::SetName(FString NewName)
{
	FText NewNameText = FText::FromString(NewName);
	
	Name->SetText(NewNameText);
}

void UMyWidget_ListEntry::SetImage(UTexture2D* NewImage)
{
	if (NewImage != nullptr)
	{
		Image->SetBrushFromTexture(NewImage);
	}
}

void UMyWidget_ListEntry::OnListItemObjectSet_Implementation(UObject* ListItemObject)
{
	AMyStructPlayer* MyPlayer = Cast<AMyStructPlayer>(ListItemObject);

	if (MyPlayer != nullptr)
	{
		SetName(MyPlayer->MyStruct.Name);
		SetHealth(MyPlayer->MyStruct.Health);
		SetImage(MyPlayer->MyStruct.Texture);
	}
}
