#include "MyActor_MCT.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AMyActor_MCT::AMyActor_MCT()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
#if WITH_EDITORONLY_DATA
	Root->bVisualizeComponent = true;
#endif
	RootComponent = Root;
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);

	LatentInfo.CallbackTarget = this;
	LatentInfo.Linkage = 0;
	LatentInfo.UUID = FGuid::NewGuid().A;
}

// Called when the game starts or when spawned
void AMyActor_MCT::BeginPlay()
{
	Super::BeginPlay();

	MoveToTarget();
}

void AMyActor_MCT::MoveToTarget()
{
	LatentInfo.ExecutionFunction = FName("ReturnToOrigin");

	UKismetSystemLibrary::MoveComponentTo(
		StaticMesh,
		TargetLocation,
		FRotator(0.f, 0.f, 0.f),
		true,
		true,
		OverTime,
		true,
		EMoveComponentAction::Move,
		LatentInfo);
}

void AMyActor_MCT::ReturnToOrigin()
{
	LatentInfo.ExecutionFunction = FName("MoveToTarget");

	UKismetSystemLibrary::MoveComponentTo(
		StaticMesh,
		FVector(0.f, 0.f, 0.f),
		FRotator(0.f, 0.f, 0.f),
		true,
		true,
		OverTime,
		true,
		EMoveComponentAction::Move,
		LatentInfo);
}
