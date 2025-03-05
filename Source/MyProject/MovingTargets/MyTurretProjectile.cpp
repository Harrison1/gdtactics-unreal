#include "MyTurretProjectile.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
// #include "MyProject/Enums/MyDamageTypes.h" 


// Sets default values
AMyTurretProjectile::AMyTurretProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComp"));
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AMyTurretProjectile::OnHit);
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 1000.f;
	ProjectileMovement->MaxSpeed = 1000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->ProjectileGravityScale = 0.f;
	InitialLifeSpan = 8.f;
}

void AMyTurretProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (IsValid(OtherActor))
	{
		AController* InstigatorController = GetInstigatorController();
		TSubclassOf<UDamageType> DamageType = UDamageType::StaticClass();
		/**
		 * Alternative Example: Pass in a specific DamageType
		 * Uncomment the above statement: #include "MyProject/Enums/MyDamageTypes.h" 
		 * TSubclassOf<UDamageType> DamageType = UMyDamageTypes::GetDamageTypeClass(EMyDamageTypes::Fire);
		 * This can sync with MyMovingTarget.cpp
		 */
		
		UGameplayStatics::ApplyDamage(OtherActor, 100.f, InstigatorController, this, DamageType);
		Destroy();
	}
}
