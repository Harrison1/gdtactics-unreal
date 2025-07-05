#include "ActivationPad.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MyProject/Prototype/PrototypeInterface.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"

AActivationPad::AActivationPad()
{
	PrimaryActorTick.bCanEverTick = false;

	Base = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base"));
	RootComponent = Base;

	Pad = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pad"));
	Pad->SetupAttachment(RootComponent);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetupAttachment(RootComponent);
}

void AActivationPad::StartAction()
{
	if (InterfaceActors.IsEmpty())
	{
		TArray<AActor*> OverlappingActors;
		BoxComponent->GetOverlappingActors(OverlappingActors, AActor::StaticClass());

		for (AActor* Actor : OverlappingActors)
		{
			if (Actor->Implements<UPrototypeInterface>())
			{
				InterfaceActors.AddUnique(Actor);
			}
		}
	}

	for (AActor* Actor : InterfaceActors)
	{
		IPrototypeInterface::Execute_Interact(Actor);
	}

	if (PressureSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, PressureSound, GetActorLocation());
	}

	if (Steam != nullptr)
	{
		FFXSystemSpawnParameters SpawnParams;
		SpawnParams.WorldContextObject = this;
		SpawnParams.SystemTemplate = Steam;
		SpawnParams.Location = GetActorLocation();
		SpawnParams.Rotation = GetActorRotation();
		SpawnParams.Scale = FVector(2.f, 2.f, 1.f);
		SpawnParams.bAutoDestroy = true;
		SpawnParams.bAutoActivate = true;
		
		UNiagaraFunctionLibrary::SpawnSystemAtLocationWithParams(SpawnParams);
	}
}

void AActivationPad::StopAction()
{
	for (AActor* Actor : InterfaceActors)
	{
		IPrototypeInterface::Execute_StopInteract(Actor);
	}
}
