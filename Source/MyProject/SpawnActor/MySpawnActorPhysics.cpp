#include "MySpawnActorPhysics.h"


// Sets default values
AMySpawnActorPhysics::AMySpawnActorPhysics()
{
	MyStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyStaticMeshComponent"));
	MyStaticMeshComponent->SetSimulatePhysics(true);
	RootComponent = MyStaticMeshComponent;
}
