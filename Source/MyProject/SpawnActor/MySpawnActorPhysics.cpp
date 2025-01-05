#include "MySpawnActorPhysics.h"


// Sets default values
AMySpawnActorPhysics::AMySpawnActorPhysics()
{
	PrimaryActorTick.bCanEverTick = false;

	MyStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyStaticMeshComponent"));
	MyStaticMeshComponent->SetSimulatePhysics(true);
	RootComponent = MyStaticMeshComponent;
}
