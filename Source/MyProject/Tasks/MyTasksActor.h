#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyTasksActor.generated.h"

UCLASS()
class MYPROJECT_API AMyTasksActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMyTasksActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY()
	USceneComponent* MyRoot;

	void FunctionA();
	void FunctionB();
	void FunctionC();
	void FunctionD();
};
