#include "SaveGameFlagPole.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"


ASaveGameFlagPole::ASaveGameFlagPole()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
#if WITH_EDITORONLY_DATA
	Root->bVisualizeComponent = true;
#endif
	RootComponent = Root;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(RootComponent);

	FlagMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FlagMesh"));
	FlagMesh->SetupAttachment(RootComponent);

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(RootComponent);

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ASaveGameFlagPole::OnBeginOverlap);
}

// Called when the game starts
void ASaveGameFlagPole::BeginPlay()
{
	Super::BeginPlay();

	FlagOriginLocation = FlagMesh->GetRelativeLocation();
}

void ASaveGameFlagPole::OnLoadGame_Implementation()
{
	if (bActive)
	{
		FlagMesh->SetRelativeLocation(TargetLocation);
	}
}

void ASaveGameFlagPole::OnResetData_Implementation()
{
	bActive = false;
	FlagMesh->SetRelativeLocation(FlagOriginLocation);
}

void ASaveGameFlagPole::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr && OtherActor != this)
	{
		bActive = true;
		
		FLatentActionInfo LatentInfo;
		LatentInfo.CallbackTarget = this;
		LatentInfo.Linkage = 0;
		LatentInfo.UUID = FGuid::NewGuid().A;

		UKismetSystemLibrary::MoveComponentTo(
			FlagMesh,
			TargetLocation,
			FRotator(0.f, 0.f, 0.f),
			true,
			true,
			3.f,
			true,
			EMoveComponentAction::Move,
			LatentInfo);
	}
}
