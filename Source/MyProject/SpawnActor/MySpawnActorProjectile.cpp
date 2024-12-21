#include "MySpawnActorProjectile.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
AMySpawnActorProjectile::AMySpawnActorProjectile()
{
	MyCollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("MyCollisionComp"));
	MyCollisionComp->SetBoxExtent(FVector(100.0f, 100.0f, 100.0f));
	MyCollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	MyCollisionComp->OnComponentHit.AddDynamic(this, &AMySpawnActorProjectile::OnHit);
	MyCollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	MyCollisionComp->CanCharacterStepUpOn = ECB_No;
	RootComponent = MyCollisionComp;

	MyMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	MyMovementComp->UpdatedComponent = MyCollisionComp;
	MyMovementComp->InitialSpeed = 50.f;
	MyMovementComp->MaxSpeed = 5000.f;
	MyMovementComp->ProjectileGravityScale = 0.f;
	InitialLifeSpan = 6.0f;
}

void AMySpawnActorProjectile::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AMySpawnActorProjectile::Accelerate, 0.1f, true, 0.f);
}

void AMySpawnActorProjectile::Accelerate()
{
	FVector NewVelocity = MyMovementComp->Velocity * 1.5f;
	MyMovementComp->Velocity = NewVelocity;
}

void AMySpawnActorProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Destroy();
}
