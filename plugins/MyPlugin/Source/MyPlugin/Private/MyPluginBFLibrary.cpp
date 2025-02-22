#include "MyPluginBFLibrary.h"

UMyPluginBFLibrary::UMyPluginBFLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

float UMyPluginBFLibrary::GetDistanceToActorInFront(AActor* MyActor, const float TraceLength)
{
	if (MyActor == nullptr) { return 0.f; }
	
	UWorld* const World = MyActor->GetWorld(); 
	FVector StartLocation = MyActor->GetActorLocation();
	FVector TraceDistance = MyActor->GetActorForwardVector() * TraceLength;
	FVector EndLocation = StartLocation + TraceDistance;
	FHitResult OutHit;

	bool bHit = World->LineTraceSingleByChannel(OutHit, StartLocation, EndLocation, ECC_Visibility);

	if (bHit)
	{
		return OutHit.Distance;
	}
	else
	{
		return 0.f;
	}
}
