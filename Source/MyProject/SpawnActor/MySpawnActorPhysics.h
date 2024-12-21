// Copyright HM Interactive, LLC. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MySpawnActorPhysics.generated.h"

UCLASS()
class MYPROJECT_API AMySpawnActorPhysics : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMySpawnActorPhysics();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* MyStaticMeshComponent;
};
