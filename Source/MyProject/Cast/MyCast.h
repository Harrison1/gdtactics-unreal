#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyCast.generated.h"

class UBoxComponent;

UCLASS()
class MYPROJECT_API AMyCast : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMyCast();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere)
	USceneComponent* MyRoot;

	UPROPERTY(EditAnywhere)
	UBoxComponent* MyBoxComponent;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
