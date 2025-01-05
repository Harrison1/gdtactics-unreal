#include "MyActorTimer.h"
#include "Components/BoxComponent.h"

// Sets default values
AMyActorTimer::AMyActorTimer()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
#if WITH_EDITORONLY_DATA
	Root->bVisualizeComponent = true;
#endif
	Root->SetVisibility(true);
	RootComponent = Root;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box->SetHiddenInGame(false);
	Box->SetBoxExtent(FVector(128.f, 128.f, 128.f));
	Box->SetupAttachment(RootComponent);

	Box->OnComponentBeginOverlap.AddDynamic(this, &AMyActorTimer::OnBeginOverlap);
	Box->OnComponentEndOverlap.AddDynamic(this, &AMyActorTimer::OnEndOverlap);
}

void AMyActorTimer::StartTimer()
{
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AMyActorTimer::TimerFunction, 1.0f, true, 0.f);
}

void AMyActorTimer::StopTimer()
{
	GetWorldTimerManager().ClearTimer(TimerHandle);
}

void AMyActorTimer::TimerFunction()
{
	FString Message = FString::Printf(TEXT("Game Time Seconds: %f"), GetWorld()->GetTimeSeconds());
	
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, Message);
	}
}

void AMyActorTimer::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	StartTimer();
}

void AMyActorTimer::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	StopTimer();
}
