#include "MySpawnActorParticle.h"
#include "NiagaraComponent.h"


// Sets default values
AMySpawnActorParticle::AMySpawnActorParticle()
{
	MyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("MyRoot"));
	MyRoot->bVisualizeComponent = true;
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
