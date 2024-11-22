#include "InterfaceTriggerVolume.h"
#include "MyInterface.h"

// Sets default values
AInterfaceTriggerVolume::AInterfaceTriggerVolume()
{
	OnActorBeginOverlap.AddDynamic(this, &AInterfaceTriggerVolume::BeginOverlap);
}

void AInterfaceTriggerVolume::BeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor != nullptr && !MyActors.IsEmpty())
	{
		for (AActor* MyActor : MyActors)
		{
			// Engine crashes if the actor does not implement the interface
			// Alt: MyActor->GetClass()->ImplementsInterface(UMyInterface::StaticClass())
			if (MyActor->Implements<UMyInterface>())
			{
				IMyInterface::Execute_PerformAction(MyActor);
			}
		}

		// Unregister from overlap event
		// Alt: Destroy();
		OnActorBeginOverlap.RemoveAll(this);
	}
}
