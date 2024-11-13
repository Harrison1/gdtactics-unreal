#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FLogWriter.h"
#include "MyDelegateBindActor.generated.h"

UCLASS()
class MYPROJECT_API AMyDelegateBindActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMyDelegateBindActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	FStringDelegate WriteToLogDelegate;
};
