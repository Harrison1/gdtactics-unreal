#include "MyPointLightToggleTrigger.h"
#include "MyPointLight.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"


// Sets default values
AMyPointLightToggleTrigger::AMyPointLightToggleTrigger()
{
	MyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("MyRoot"));
#if WITH_EDITORONLY_DATA
	MyRoot->bVisualizeComponent = true;
#endif
	RootComponent = MyRoot;

	MyStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyStaticMesh"));
	MyStaticMesh->SetupAttachment(RootComponent);

	MyTextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("MyTextRenderComponent"));
	MyTextRenderComponent->SetupAttachment(RootComponent);

	MyBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("MyBoxComponent"));
	MyBoxComponent->SetupAttachment(RootComponent);

	MyBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AMyPointLightToggleTrigger::OnBeginOverlap);
	MyBoxComponent->OnComponentEndOverlap.AddDynamic(this, &AMyPointLightToggleTrigger::OnEndOverlap);
}

void AMyPointLightToggleTrigger::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr && OtherActor != this)
	{
		for (AMyPointLight* MyPointLight : MyPointLights)
		{
			MyPointLight->ToggleTimer();
		}
	}
}

void AMyPointLightToggleTrigger::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor != nullptr && OtherActor != this)
	{
		for (AMyPointLight* MyPointLight : MyPointLights)
		{
			MyPointLight->ToggleTimer();
		}
	}
}
