#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MyHelpers.generated.h"


UCLASS()
class MYPROJECT_API UMyHelpers : public UObject
{
	GENERATED_BODY()

public:

	UFUNCTION()
	static FVector AimAheadLocation(FVector ActorLocation, float ProjectileSpeed, FVector TargetLocation, FVector TargetVelocity);
	
	UFUNCTION()
	static FRotator LookAtAimAheadLocation(FVector ActorLocation, float ProjectileSpeed, FVector TargetLocation, FVector TargetVelocity);
};
