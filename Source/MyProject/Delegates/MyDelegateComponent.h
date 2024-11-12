#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MyDelegateComponent.generated.h"

UDELEGATE(BlueprintCallable)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdateManaCPP, float, ManaValue);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MYPROJECT_API UMyDelegateComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	/** Delegate to whom anyone can subscribe to receive this event */
	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "Mana")
	FUpdateManaCPP UpdateManaCPP;
};
