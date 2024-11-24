#include "MyWidget_Health.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UMyWidget_Health::SetHealth(float NewHealth)
{
	float NewHealthPct = NewHealth / 100.f;

	HealthBar->SetPercent(NewHealthPct);
}

void UMyWidget_Health::SetName(FString NewName)
{
	FText NewNameText = FText::FromString(NewName);
	
	Name->SetText(NewNameText);
}
