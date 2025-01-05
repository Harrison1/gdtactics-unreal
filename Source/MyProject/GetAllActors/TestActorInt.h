#pragma once

#include "CoreMinimal.h"
#include "TestActor.h"
#include "MyProject/Interfaces/MyInterface.h"
#include "TestActorInt.generated.h"

UCLASS()
class MYPROJECT_API ATestActorInt : public ATestActor, public IMyInterface
{
	GENERATED_BODY()
};
