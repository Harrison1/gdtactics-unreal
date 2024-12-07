#include "SaveGameTriggerSphere.h"
#include "Components/SphereComponent.h"
#include "Components/TextRenderComponent.h"
#include "SaveGameSubsystem.h"


// Sets default values
ASaveGameTriggerSphere::ASaveGameTriggerSphere()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Root->bVisualizeComponent = true;
	RootComponent = Root;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	Text = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Text"));
	Text->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
	Text->SetupAttachment(RootComponent);

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetHiddenInGame(false);
	Sphere->SetupAttachment(RootComponent);

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ASaveGameTriggerSphere::OnBeginOverlap);
}

void ASaveGameTriggerSphere::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr && OtherActor != this)
	{
		if (bLoadGame)
		{
			LoadGame();
			return;
		}
		
		if (bSaveGame)
		{
			SaveGame();
			return;
		}

		if (bResetData) ResetData();
	}
}

void ASaveGameTriggerSphere::LoadGame()
{
	USaveGameSubsystem* SaveSubsystem = GetGameInstance()->GetSubsystem<USaveGameSubsystem>();
	SaveSubsystem->LoadGame();
}

void ASaveGameTriggerSphere::ResetData()
{
	USaveGameSubsystem* SaveSubsystem  = GetGameInstance()->GetSubsystem<USaveGameSubsystem>();
	SaveSubsystem->ResetData();
}

void ASaveGameTriggerSphere::SaveGame()
{
	USaveGameSubsystem* SaveSubsystem  = GetGameInstance()->GetSubsystem<USaveGameSubsystem>();
	SaveSubsystem->SaveGame();
}
