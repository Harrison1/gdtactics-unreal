#include "MyMovingTargetTrigger.h"
#include "Components/BoxComponent.h"
#include "EngineUtils.h"
#include "MyMovingTargetInterface.h"


// Sets default values
AMyMovingTargetTrigger::AMyMovingTargetTrigger()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
#if WITH_EDITORONLY_DATA
	Root->bVisualizeComponent = true;
#endif
	RootComponent = Root;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(Root);

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AMyMovingTargetTrigger::OnBeginOverlap);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &AMyMovingTargetTrigger::OnEndOverlap);
}

void AMyMovingTargetTrigger::TriggerInterfaceAction()
{
	for (AActor* Actor : TActorRange<AActor>(GetWorld()))
	{
		if (!Actor->Implements<UMyMovingTargetInterface>())
		{
			continue;
		}

		IMyMovingTargetInterface::Execute_ToggleActivation(Actor);
	}
}

void AMyMovingTargetTrigger::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr && OtherActor != this)
	{
		TriggerInterfaceAction();
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Moving Target Demo Starting"));
		}
	}
}

void AMyMovingTargetTrigger::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor != nullptr && OtherActor != this)
	{
		TriggerInterfaceAction();
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Moving Target Demo Ending"));
		}
	}
}
