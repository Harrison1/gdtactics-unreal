#include "MyStructBoundingBox.h"
#include "MyStructPlayer.h"
#include "Components/BoxComponent.h"
#include "GameFramework/PlayerController.h"

// Sets default values
AMyStructBoundingBox::AMyStructBoundingBox()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Root->bVisualizeComponent = true;
	RootComponent = Root;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box->SetHiddenInGame(false);
	Box->SetupAttachment(RootComponent);
}

TArray<AActor*> AMyStructBoundingBox::GetPlayers()
{
	TArray<AActor*> OutOverlappingActors;
	Box->GetOverlappingActors(OutOverlappingActors, AMyStructPlayer::StaticClass());

	return OutOverlappingActors;
}
