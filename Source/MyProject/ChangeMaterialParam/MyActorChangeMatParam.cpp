#include "MyActorChangeMatParam.h"

// Sets default values
AMyActorChangeMatParam::AMyActorChangeMatParam()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Root->bVisualizeComponent = true;
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
