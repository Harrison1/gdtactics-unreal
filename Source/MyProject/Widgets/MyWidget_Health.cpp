#include "MyWidget_Health.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UMyWidget_Health::SetHealth(float NewHealth)
{
	float HealthPercentage = NewHealth / 100.f;

	HealthBar->SetPercent(HealthPercentage);
}

void UMyWidget_Health::SetName(FString NewName)
{
	FText NewNameText = FText::FromString(NewName);
	Name->SetText(NewNameText);
}
