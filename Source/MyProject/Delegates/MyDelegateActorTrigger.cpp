#include "MyDelegateActorTrigger.h"
#include "MyDelegateComponent.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"

// Sets default values
AMyDelegateActorTrigger::AMyDelegateActorTrigger()
{
	PrimaryActorTick.bCanEverTick = false;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
#if WITH_EDITORONLY_DATA
	DefaultSceneRoot->bVisualizeComponent = true;
#endif
	RootComponent = DefaultSceneRoot;
	
	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyMesh"));
	MyMesh->SetupAttachment(RootComponent);

	MyText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("MyText"));
	MyText->SetupAttachment(RootComponent);

	MyBox = CreateDefaultSubobject<UBoxComponent>(TEXT("MyBox"));
	MyBox->OnComponentBeginOverlap.AddDynamic(this, &AMyDelegateActorTrigger::OnBeginOverlap);
	MyBox->SetupAttachment(RootComponent);
}

void AMyDelegateActorTrigger::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		UMyDelegateComponent* MyDelComp = OtherActor->FindComponentByClass<UMyDelegateComponent>();
		
		if (MyDelComp != nullptr)
		{
			MyDelComp->UpdateManaCPP.Broadcast(ManaValue);
		}
	}
}
