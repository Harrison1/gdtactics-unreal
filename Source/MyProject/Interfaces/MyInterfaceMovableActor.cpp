#include "MyInterfaceMovableActor.h"
#include "Components/BillboardComponent.h"
#include "Components/TimelineComponent.h"
#include "Curves/CurveFloat.h"

// Sets default values
AMyInterfaceMovableActor::AMyInterfaceMovableActor()
{
	DefaultSceneRoot = CreateDefaultSubobject<UBillboardComponent>(TEXT("DefaultScenRoot"));
	RootComponent = DefaultSceneRoot;
	
	MovableMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MovableMesh"));
	MovableMesh->SetupAttachment(RootComponent);
	
	MyTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("MyTimeline"));
}

// Called when the game starts or when spawned
void AMyInterfaceMovableActor::BeginPlay()
{
	Super::BeginPlay();

	if (AlphaCurve != nullptr)
	{
		FOnTimelineFloat InterpFunc;
		
		InterpFunc.BindUFunction(this, FName("MoveMesh"));

		MyTimeline->AddInterpFloat(AlphaCurve, InterpFunc, FName("Alpha"), FName("Alpha"));
	}
}

void AMyInterfaceMovableActor::PerformAction_Implementation()
{
	// Alternative: MyTimeline->PlayFromStart();
	MyTimeline->Play();
}

void AMyInterfaceMovableActor::MoveMesh(float Value)
{
	FVector NewLocation = FMath::Lerp(MovableMesh->GetRelativeLocation(), FVector(0.f, 0.f, 0.f), Value);
	MovableMesh->SetRelativeLocation(NewLocation);
}
