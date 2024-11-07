#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyInterface.h"
#include "MyInterfaceDestroyActor.generated.h"

UCLASS()
class MYPROJECT_API AMyInterfaceDestroyActor : public AActor, public IMyInterface
{
	GENERATED_BODY()

public:
	// Blueprint Native Event override
	void PerformAction_Implementation() override;
};
