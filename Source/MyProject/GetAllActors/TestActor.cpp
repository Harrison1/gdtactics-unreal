#include "TestActor.h"
#include "UObject/ConstructorHelpers.h"


// Sets default values
ATestActor::ATestActor()
{
	PrimaryActorTick.bCanEverTick = false;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;

	if (FMath::RandBool())
	{
		Tags.Add(TEXT("MyTag"));
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MyAsset(TEXT("/Engine/BasicShapes/Cube.Cube"));

	if (MyAsset.Succeeded())
	{
		StaticMesh->SetStaticMesh(MyAsset.Object);
		StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}
