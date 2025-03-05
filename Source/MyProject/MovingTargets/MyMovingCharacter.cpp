#include "MyMovingCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
// #include "MyProject/Enums/MyDamageTypes.h" 


// Sets default values
AMyMovingCharacter::AMyMovingCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCharacterMovement()->GravityScale = 0.f;
	GetCharacterMovement()->MaxAcceleration = 20480.f;
	GetCharacterMovement()->DisableMovement();

	OnTakeAnyDamage.AddDynamic(this, &AMyMovingCharacter::ProcessDamage);
}

// Called when the game starts or when spawned
void AMyMovingCharacter::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickEnabled(false);
	SetActorHiddenInGame(true);
	Origin = GetActorTransform();
}

// Called every frame
void AMyMovingCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	GetCharacterMovement()->AddInputVector(GetActorForwardVector());
}

// Called to bind functionality to input
void AMyMovingCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AMyMovingCharacter::ToggleActivation_Implementation()
{
	IMyMovingTargetInterface::ToggleActivation_Implementation();
	
	if (bActive)
	{
		bActive = false;
		Deactivate();
		GetWorldTimerManager().ClearTimer(SpawnTimerHandle);
	}
	else
	{
		bActive = true;
		Activate();
	}
}

void AMyMovingCharacter::SpawnActor()
{
	if (SpawnPoints.Num() > 0)
	{
		int32 RandomIndex = FMath::RandRange(0, SpawnPoints.Num() - 1);
		AActor* NewSpawnActor = SpawnPoints[RandomIndex];
		SpawnPoint = NewSpawnActor->GetActorTransform();
	}
	else
	{
		SpawnPoint = Origin;
	}
	
	SetActorTransform(SpawnPoint);
}


void AMyMovingCharacter::Activate()
{
	GetWorldTimerManager().ClearTimer(SpawnTimerHandle);
	SpawnActor();
	Health = 50.f;
	const float RandomSpeed = FMath::RandRange(400.f, 700.f);

	GetCharacterMovement()->MaxWalkSpeed = RandomSpeed;
	GetCharacterMovement()->MinAnalogWalkSpeed = RandomSpeed;
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetCharacterMovement()->GravityScale = 1.f;
	SetActorHiddenInGame(false);
	SetActorTickEnabled(true);
}


void AMyMovingCharacter::Deactivate()
{
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	GetCharacterMovement()->GravityScale = 0.f;
	GetCharacterMovement()->DisableMovement();
	UE_LOG(LogTemp, Warning, TEXT("AMyMovingCharacter::Deactivate"));
	
	GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &AMyMovingCharacter::Activate, 1.0f, false);
}

void AMyMovingCharacter::ProcessDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	Health -= Damage;
	
	if (Health <= 0.f)
	{
		Deactivate();
	}

	/**
	 * Alternativly when reacting to a custom DamageType we can perform logic based on type
	 * Uncomment the above statement: #include "MyProject/Enums/MyDamageTypes.h"
	 * This can sync with MyTurretProjectile.cpp
	 *
	 * 	if (DamageType != nullptr)
	 *	{
	 *		if (DamageType->IsA(UGasDamageType::StaticClass()))
	 *		{
	 *			// Gas Damage Type
	 *			UE_LOG(LogTemp, Warning, TEXT("Gas DamageType"));
	 *			// Perform Logic
	 *		}
	 *		else if (DamageType->IsA(UFireDamageType::StaticClass()))
	 *		{
	 *			// Fire Damage Type
	 *			UE_LOG(LogTemp, Warning, TEXT("Fire DamageType"));
	 *			// Perform Logic
	 *		}
	 *		else if (DamageType->IsA(UWaterDamageType::StaticClass()))
	 *		{
	 *			// Water Damage Type
	 *			UE_LOG(LogTemp, Warning, TEXT("Water DamageType"));
	 *			// Perform Logic
	 *		}
	 *		else
	 *		{
	 *		     UE_LOG(LogTemp, Warning, TEXT("Default DamageType"));
	 *			// Perform Logic
	 *		}
	 *	}
	 */
}
