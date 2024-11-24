#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyStruct.h"
#include "MyStructActor.generated.h"

class UBoxComponent;

UCLASS()
class MYPROJECT_API AMyStructActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMyStructActor();
	
	UPROPERTY(EditAnywhere)
	USceneComponent* Root;

	UPROPERTY(EditAnywhere)
	UBoxComponent* Box;

	UPROPERTY(EditAnywhere)
	UUserWidget* MyUserWidget;
	
	UPROPERTY(EditAnywhere)
	TArray<FMyStruct> Players;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
