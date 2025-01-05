#include "MyCameraShakeTrigger.h"
#include "MyCameraShake.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AMyCameraShakeTrigger::AMyCameraShakeTrigger()
{
	PrimaryActorTick.bCanEverTick = false;

	MyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("MyRoot"));
#if WITH_EDITORONLY_DATA
	MyRoot->bVisualizeComponent = true;
#endif
	RootComponent = MyRoot;

	MyBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("MyBoxComponent"));
	MyBoxComponent->SetHiddenInGame(false);
	MyBoxComponent->SetupAttachment(RootComponent);

	MyBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AMyCameraShakeTrigger::OnBeginOverlap);
}

void AMyCameraShakeTrigger::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr && OtherActor != this)
	{
		// Get the player controller
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
		if (PlayerController)
		{
			// Specify the Camera Shake class
			TSubclassOf<UMyCameraShake> CameraShakeClass = UMyCameraShake::StaticClass();
			if (CameraShakeClass)
			{
				// Play the camera shake
				PlayerController->ClientStartCameraShake(CameraShakeClass);
			}
		}
	}
}