#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyStruct.h"
#include "MyStructPlayer.generated.h"

class USkeletalMeshComponent;
class UWidgetComponent;

UCLASS()
class MYPROJECT_API AMyStructPlayer : public AActor
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Sets default values for this actor's properties
	AMyStructPlayer();

	UPROPERTY(EditAnywhere)
	USceneComponent* Root;

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FMyStruct MyStruct;

	UPROPERTY(EditAnywhere)
	UWidgetComponent* Widget;
};
