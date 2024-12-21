#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MySpawnActorParticle.generated.h"

class UNiagaraComponent;

UCLASS()
class MYPROJECT_API AMySpawnActorParticle : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMySpawnActorParticle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY()
	USceneComponent* MyRoot;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UNiagaraComponent* MyNiagaraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialInterface* MyMaterialInterface;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector ParticleColor;
};
