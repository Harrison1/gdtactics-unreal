#include "MyWidget_ListEntry.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "MyProject/Structs/MyStructPlayer.h"

// void UMyWidget_ListEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
// {
// 	Super::NativeOnListItemObjectSet(ListItemObject);
//
// 	// Additional logic here if needed
// }

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

void UMyWidget_ListEntry::OnListItemObjectSet_Implementation(UObject* ListItemObject)
{
	UE_LOG(LogTemp, Warning, TEXT("OnListItemObjectSet_Implementation"));
	AMyStructPlayer* MyPlayer = Cast<AMyStructPlayer>(ListItemObject);

	if (MyPlayer != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("2222222"));
		SetName(MyPlayer->Name);
		SetHealth(MyPlayer->Health);
	}
}
