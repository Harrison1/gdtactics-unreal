#include "MyActorChangeMatParam.h"

// Sets default values
AMyActorChangeMatParam::AMyActorChangeMatParam()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
#if WITH_EDITORONLY_DATA
	// Root->bVisualizeComponent = true;
#endif
	RootComponent = Root;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AMyActorChangeMatParam::BeginPlay()
{
	Super::BeginPlay();

	if (StaticMesh != nullptr)
	{
		UMaterialInterface* Material = StaticMesh->GetMaterial(0);

		if (Material != nullptr)
		{
			DynamicMaterial = UMaterialInstanceDynamic::Create(Material, StaticMesh);

			if (DynamicMaterial != nullptr)
			{
				StaticMesh->SetMaterial(0, DynamicMaterial);
			}
		}
	}

	UpdateMaterial();
}

void AMyActorChangeMatParam::UpdateMaterial(FVector Color, float Emissive, bool Randomize)
{
	if (DynamicMaterial != nullptr)
	{
		if (Randomize)
		{
			Color = FMath::VRand();
			Emissive = FMath::FRand() * 10.f;
		}
		
		DynamicMaterial->SetVectorParameterValue(VectorParamName, Color);
		DynamicMaterial->SetScalarParameterValue(ScalarParamName, Emissive);
	}
}

void AMyActorChangeMatParam::StartTimer()
{
	UpdateMaterial();
}

void AMyActorChangeMatParam::Interact_Implementation()
{
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AMyActorChangeMatParam::StartTimer, 0.5f, true, 0.f);
}

void AMyActorChangeMatParam::StopInteract_Implementation()
{
	GetWorldTimerManager().ClearTimer(TimerHandle);
}
