#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActorLineTrace.generated.h"

UCLASS()
class MYPROJECT_API AMyActorLineTrace : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMyActorLineTrace();
	
	UPROPERTY(EditAnywhere)
	USceneComponent* Root;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere)
	int32 TestFunc = 0;

	UFUNCTION(BlueprintCallable)
	void SingleLineTrace();
};
