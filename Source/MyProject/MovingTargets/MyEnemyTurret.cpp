#include "MyEnemyTurret.h"
#include "MyMovingCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "MyProject/Helpers/MyHelpers.h"
#include "MyTurretProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AMyEnemyTurret::AMyEnemyTurret()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetActorTickInterval(2.f);
}

// Called when the game starts or when spawned
void AMyEnemyTurret::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickEnabled(false);
}

// Called every frame
void AMyEnemyTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsValid(MyMovingCharacter))
	{
		if (MyMovingCharacter->IsHidden())
		{
			return;
		}

		FVector ActorLocation = GetActorLocation();
		FVector TargetLocation = MyMovingCharacter->GetActorLocation();
		FVector TargetVelocity = MyMovingCharacter->GetVelocity();
		float ProjectileSpeed = FMath::RandRange(1000.f, 3000.f);
		
		FRotator NewRotation = UMyHelpers::LookAtAimAheadLocation(ActorLocation, ProjectileSpeed, TargetLocation, TargetVelocity);

		SetActorRotation(NewRotation);
		ShootProjectile(ProjectileSpeed);
	}
}

void AMyEnemyTurret::ToggleActivation_Implementation()
{
	IMyMovingTargetInterface::ToggleActivation_Implementation();

	if (IsActorTickEnabled())
	{
		GetWorldTimerManager().ClearTimer(ActivateTimerHandle);
		SetActorTickEnabled(false);
	}
	else
	{
		GetWorldTimerManager().SetTimer(ActivateTimerHandle,
			FTimerDelegate::CreateLambda([this]()
			{
				SetActorTickEnabled(true);
			}), 1.f, false);
		}
}

void AMyEnemyTurret::ShootProjectile(float ProjectileSpeed)
{
	if (MyTurretProjectileClass != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			FTransform SpawnTransform(GetActorTransform());
					
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			AMyTurretProjectile* MyProjectile = World->SpawnActorDeferred<AMyTurretProjectile>(MyTurretProjectileClass, SpawnTransform, nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

			if (MyProjectile)
			{
				// We can now access class variables before spawning 
				MyProjectile->ProjectileMovement->InitialSpeed = ProjectileSpeed;
				MyProjectile->ProjectileMovement->MaxSpeed = ProjectileSpeed;
				
				UGameplayStatics::FinishSpawningActor(MyProjectile, SpawnTransform);	
			}
		}
	}
}
