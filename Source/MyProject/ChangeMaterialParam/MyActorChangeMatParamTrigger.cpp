#include "MyActorChangeMatParamTrigger.h"
#include "Components/BoxComponent.h"
#include "MyActorChangeMatParam.h"

// Sets default values
AMyActorChangeMatParamTrigger::AMyActorChangeMatParamTrigger()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Roort"));
#if WITH_EDITORONLY_DATA
	Root->bVisualizeComponent = true;
#endif
	RootComponent = Root;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box->SetupAttachment(Root);

	Box->OnComponentBeginOverlap.AddDynamic(this, &AMyActorChangeMatParamTrigger::OnBeginOverlap);
	Box->OnComponentEndOverlap.AddDynamic(this, &AMyActorChangeMatParamTrigger::OnEndOverlap);
}

void AMyActorChangeMatParamTrigger::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	RandomizeParams();
}

void AMyActorChangeMatParamTrigger::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	RandomizeParams();
}

void AMyActorChangeMatParamTrigger::RandomizeParams()
{
	for (AMyActorChangeMatParam* MatActor : MyMatActors)
	{
		MatActor->UpdateMaterial();
	}
}
