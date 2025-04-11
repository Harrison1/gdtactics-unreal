#include "MyActorCPD.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
AMyActorCPD::AMyActorCPD()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;
}

// Called when the game starts or when spawned
void AMyActorCPD::BeginPlay()
{
	Super::BeginPlay();

	if (StaticMesh != nullptr)
	{
		FVector4 BaseColor = FVector4(0.002428f, 0.138432f, 0.57758f, 0.1f);

		StaticMesh->SetCustomPrimitiveDataVector4(0, BaseColor);
		StaticMesh->SetCustomPrimitiveDataFloat(4, 0.f);
		StaticMesh->SetCustomPrimitiveDataFloat(5, 1.f);
	}
}

void AMyActorCPD::StartTimer()
{
	if (StaticMesh != nullptr)
	{
		GetWorldTimerManager().SetTimer(TimerHandle, this, &AMyActorCPD::TimerFunction, 1.0f, true, 0.f);
	}
}

void AMyActorCPD::StopTimer()
{
	GetWorldTimerManager().ClearTimer(TimerHandle);
}

void AMyActorCPD::TimerFunction() const
{
	const float Red = UKismetMathLibrary::RandomFloatInRange(0, 1);
	const float Green = UKismetMathLibrary::RandomFloatInRange(0, 1);
	const float Blue = UKismetMathLibrary::RandomFloatInRange(0, 1);
	const float Emissive = UKismetMathLibrary::RandomFloatInRange(-15, 5);
	const float Scale = UKismetMathLibrary::RandomFloatInRange(0.1f, 80.f);
	
	const FVector4 BaseColor = FVector4(Red, Green, Blue, 1.f);
	
	StaticMesh->SetCustomPrimitiveDataVector4(0, BaseColor);
	StaticMesh->SetCustomPrimitiveDataFloat(4, Emissive);
	StaticMesh->SetCustomPrimitiveDataFloat(5, Scale);
}
