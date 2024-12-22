#include "MySpawnActor.h"
#include "MySpawnActorParticle.h"
#include "MySpawnActorPhysics.h"
#include "MySpawnActorProjectile.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AMySpawnActor::AMySpawnActor()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Root->bVisualizeComponent = true;
	RootComponent = Root;
}

void AMySpawnActor::SpawnActor_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("SpawnActor_Implementation"));

	if (bSpawnPhysicsActor)
	{
		SpawnPhysicsActor();
	}
	else if (bSpawnProjectileActor)
	{
		SpawnProjectileActor();
	}
	else if (bSpawnParticleEffect)
	{
		SpawnParticleEffect();
	}
}

void AMySpawnActor::SpawnPhysicsActor()
{
	if (MySpawnActorPhysicsClass != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			const FVector SpawnLocation = GetActorLocation();
			// Set Rotation: Pitch and Yaw randomized to prevent perfect stacking.
			const FRotator SpawnRotation = FRotator(FMath::RandRange(0.0f, 360.0f), 0.f, FMath::RandRange(0.0f, 360.0f));
			
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			World->SpawnActor<AActor>(MySpawnActorPhysicsClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
		}
	}
}

void AMySpawnActor::SpawnProjectileActor()
{
	if (MySpawnActorProjectileClass != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			const FVector SpawnLocation = GetActorLocation();
			const FRotator SpawnRotation = GetActorRotation();
			
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			World->SpawnActor<AActor>(MySpawnActorProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
		}
	}
}

void AMySpawnActor::SpawnParticleEffect()
{
	if (MySpawnActorParticleClass != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			FTransform SpawnTransform;
			SpawnTransform.SetLocation(GetActorLocation());
			SpawnTransform.SetRotation(FRotator::ZeroRotator.Quaternion());
			SpawnTransform.SetScale3D(FVector(1.f));
			
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			AMySpawnActorParticle* MyDeferredActor = World->SpawnActorDeferred<AMySpawnActorParticle>(MySpawnActorParticleClass, SpawnTransform, nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

			if (MyDeferredActor)
			{
				// We can now access class variables before spawning 
				MyDeferredActor->ParticleColor = RandomColor();

				UGameplayStatics::FinishSpawningActor(MyDeferredActor, SpawnTransform);	
			}
		}
	}
}

FVector AMySpawnActor::RandomColor()
{
	float Red = FMath::RandRange(0.f, 1.f);
	float Blue = FMath::RandRange(0.f, 1.f);
	float Green = FMath::RandRange(0.f, 1.f);

	return FVector(Red, Blue, Green);
}
