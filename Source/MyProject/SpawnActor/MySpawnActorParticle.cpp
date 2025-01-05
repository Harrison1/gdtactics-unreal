#include "MySpawnActorParticle.h"
#include "NiagaraComponent.h"


// Sets default values
AMySpawnActorParticle::AMySpawnActorParticle()
{
	PrimaryActorTick.bCanEverTick = false;

	MyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("MyRoot"));
#if WITH_EDITORONLY_DATA
	MyRoot->bVisualizeComponent = true;
#endif
	RootComponent = MyRoot;

	MyNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("MyNiagaraComponent"));
	MyNiagaraComponent->SetupAttachment(RootComponent);

	ParticleColor = FVector(1.f, 0.f, 0.f);
}

// Called when the game starts or when spawned
void AMySpawnActorParticle::BeginPlay()
{
	Super::BeginPlay();

	if (MyMaterialInterface != nullptr)
	{
		UMaterialInstanceDynamic* MyDynamicMaterialInstance = UMaterialInstanceDynamic::Create(MyMaterialInterface, MyNiagaraComponent);

		if (MyDynamicMaterialInstance != nullptr)
		{
			MyDynamicMaterialInstance->SetVectorParameterValue(FName("Base Color"), ParticleColor);

			MyNiagaraComponent->SetVariableMaterial(FName("MyMaterial"), MyDynamicMaterialInstance);
		}
	}
}
