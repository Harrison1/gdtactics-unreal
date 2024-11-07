#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"
#include "InterfaceTriggerVolume.generated.h"

UCLASS()
class MYPROJECT_API AInterfaceTriggerVolume : public ATriggerVolume
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AInterfaceTriggerVolume();

	UFUNCTION()
	void BeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> MyActors = TArray<AActor*>();
};
