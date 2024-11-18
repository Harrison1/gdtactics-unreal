#include "MyActorLineTrace.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AMyActorLineTrace::AMyActorLineTrace()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Root->bVisualizeComponent = true;
	RootComponent = Root;
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(Root);
}

void AMyActorLineTrace::SingleLineTrace()
{
	UWorld* const World = GetWorld();
	FVector Start = GetActorLocation();
	FVector End = (GetActorForwardVector() * 2000.f) + Start;
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);
	FHitResult OutHit;

	bool bHit = false;

	switch (TestFunc)
	{
		case 0:
			bHit = UKismetSystemLibrary::LineTraceSingle(
				World,
				Start,
				End,
				ETraceTypeQuery::TraceTypeQuery1,
				false,
				ActorsToIgnore,
				EDrawDebugTrace::Persistent,
				OutHit,
				true
				);
		
			break;
		case 1:
			bHit = UKismetSystemLibrary::LineTraceSingleByProfile(
				World,
				Start,
				End,
				FName("BlockAll"),
				false,
				ActorsToIgnore,
				EDrawDebugTrace::Persistent,
				OutHit,
				true
				);
		
			break;
		case 2:
			bHit = World->LineTraceSingleByChannel(
				OutHit,
				Start,
				End,
				ECC_Visibility
				);
		
			break;

		case 3:
			DrawDebugLine(World, Start, End, FColor::Red, true);

			break;
		default:
			bHit = false;
	}
	
	if (bHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Single Trace Object Name: %s"), *OutHit.HitObjectHandle.GetName());

		FString ActorDisplayName = UKismetSystemLibrary::GetDisplayName(OutHit.GetActor());
		UE_LOG(LogTemp, Warning, TEXT("Profile Trace OutHit Display Name: %s"), *ActorDisplayName);
	}
}
