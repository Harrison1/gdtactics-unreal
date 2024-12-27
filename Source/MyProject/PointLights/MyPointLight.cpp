#include "MyPointLight.h"
#include "Components/PointLightComponent.h"


// Sets default values
AMyPointLight::AMyPointLight()
{
	MyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("MyRoot"));
	RootComponent = MyRoot;

	MyPointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("MyPointLight"));
	MyPointLight->SetLightColor(FColor::MakeRandomColor());
	MyPointLight->SetIntensity(FMath::RandRange(5000.f, 10000.f));
	MyPointLight->SetUseTemperature(FMath::RandBool());
	MyPointLight->SetTemperature(FMath::RandRange(4000.f, 8000.f));
	MyPointLight->SetAttenuationRadius(FMath::RandRange(1000.f, 2000.f));
	MyPointLight->SetSourceRadius(FMath::RandRange(0.f, 100.f));
	MyPointLight->SetupAttachment(RootComponent);
}

void AMyPointLight::ToggleTimer()
{
	if (GetWorldTimerManager().IsTimerActive(TimerHandle))
	{
		GetWorldTimerManager().ClearTimer(TimerHandle);
	}
	else
	{
		GetWorldTimerManager().SetTimer(TimerHandle, this, &AMyPointLight::SetRandomColor, FMath::RandRange(1.f, 3.f), true, 0.f);
	}
}

void AMyPointLight::SetRandomColor()
{
	MyPointLight->SetLightColor(FColor::MakeRandomColor());
}
