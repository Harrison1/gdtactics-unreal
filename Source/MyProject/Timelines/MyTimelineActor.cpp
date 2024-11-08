#include "MyTimelineActor.h"
#include "Components/TimelineComponent.h"
#include "Curves/CurveFloat.h"

// Sets default values
AMyTimelineActor::AMyTimelineActor()
{
	MyTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("MyTimeline"));
}

// Called when the game starts or when spawned
void AMyTimelineActor::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();

	if (AlphaCurve != nullptr)
	{
		FOnTimelineFloat InterpFunc;
		
		InterpFunc.BindUFunction(this, FName("Update"));

		MyTimeline->AddInterpFloat(AlphaCurve, InterpFunc, FName("Alpha"), FName("Alpha"));
		MyTimeline->SetLooping(true);

		MyTimeline->PlayFromStart();
	}
}

void AMyTimelineActor::Update(float Value)
{
	FVector NewLocation = FMath::Lerp(StartLocation, EndLocation, Value);
	SetActorLocation(NewLocation);
}
