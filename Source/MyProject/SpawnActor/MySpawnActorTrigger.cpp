#include "MySpawnActorTrigger.h"
#include "Components/BoxComponent.h"
#include "MySpawnActor.h"
#include "MySpawnActorInterface.h"


// Sets default values
AMySpawnActorTrigger::AMySpawnActorTrigger()
{
	MyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("MyRoot"));
	MyRoot->bVisualizeComponent = true;
	RootComponent = MyRoot;

	MyBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("MyBoxComponent"));
	MyBoxComponent->SetupAttachment(RootComponent);

	MyBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AMySpawnActorTrigger::OnBeginOverlap);
}

void AMySpawnActorTrigger::StartTimer()
{
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AMySpawnActorTrigger::MyTimerFunction, 1.0f, true, 0.f);
}

void AMySpawnActorTrigger::MyTimerFunction()
{
	if (SpawnCounter < MaxSpawnCount)
	{
		SpawnCounter++;
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, *FString::Printf(TEXT("SpawnCounter: %d ..."), SpawnCounter));
		}
		IMySpawnActorInterface::Execute_SpawnActor(MySpawnedActor);
	}
	else
	{
		GetWorldTimerManager().ClearTimer(TimerHandle);
		MyBoxComponent->OnComponentBeginOverlap.RemoveAll(this);
	}
}

void AMySpawnActorTrigger::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr && OtherActor != this)
	{
		if (IsValid(MySpawnedActor) && MySpawnedActor->Implements<UMySpawnActorInterface>())
		{
			StartTimer();
		}
	}
}
