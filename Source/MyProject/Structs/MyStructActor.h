#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyStruct.h"
#include "MyStructActor.generated.h"

UCLASS()
class MYPROJECT_API AMyStructActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMyStructActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	TArray<FMyStruct> Players;
};
