#include "OpenLevelBoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Called when the game starts
void UOpenLevelBoxComponent::BeginPlay()
{
	Super::BeginPlay();

	// Register the Overlap Event
	OnComponentBeginOverlap.AddDynamic(this, &UOpenLevelBoxComponent::OnBoxBeginOverlap);
}

void UOpenLevelBoxComponent::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UWorld* const World = GetWorld();
	
	if (OtherActor != nullptr && !Level.IsNull())
	{
		// Doing the valid checks and using LoadSynchronous() might be optional for simple use cases
		if (!Level.IsValid())
		{
			Level.LoadSynchronous();
		}

		if (Level.IsValid())
		{
			UGameplayStatics::OpenLevelBySoftObjectPtr(World, Level);

			// Alternatively you can use OpenLevel and hard code an FName string for the level map name
			// UGameplayStatics::OpenLevel(World, "ThirdPersonMap");	
		}
	}
}
