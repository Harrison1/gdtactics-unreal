#include "SaveGameCoin.h"
#include "Components/SphereComponent.h"


// Sets default values
ASaveGameCoin::ASaveGameCoin()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
#if WITH_EDITORONLY_DATA
	Root->bVisualizeComponent = true;
#endif
	RootComponent = Root;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh->SetupAttachment(RootComponent);

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(RootComponent);

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ASaveGameCoin::OnBeginOverlap);
}

void ASaveGameCoin::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr)
	{
		Deactivate();
	}
}


void ASaveGameCoin::OnLoadGame_Implementation()
{
	if (!bActive)
	{
		Deactivate();
	}
}

void ASaveGameCoin::OnResetData_Implementation()
{
	Activate();
}

void ASaveGameCoin::Activate()
{
	bActive = true;
	Mesh->SetHiddenInGame(false);
	Sphere->OnComponentBeginOverlap.AddUniqueDynamic(this, &ASaveGameCoin::OnBeginOverlap);

	/** Alternative to AddUniqueDynamic
	 *  if (!Sphere->OnComponentBeginOverlap.IsAlreadyBound(this, &ASaveGameCoin::OnBeginOverlap))
	 *  {
	 * 	  Sphere->OnComponentBeginOverlap.AddDynamic(this, &ASaveGameCoin::OnBeginOverlap);
	 *  }
	 */
}

void ASaveGameCoin::Deactivate()
{
	bActive = false;
	Mesh->SetHiddenInGame(true);
	Sphere->OnComponentBeginOverlap.RemoveAll(this);
}
