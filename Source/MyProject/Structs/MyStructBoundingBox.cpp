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

void AMyStructBoundingBox::SetPlayers()
{
	TArray<AActor*> OutOverlappingActors;
	Box->GetOverlappingActors(OutOverlappingActors, AMyStructPlayer::StaticClass());

	for (AActor* MyPlayer : OutOverlappingActors)
	{
		AMyStructPlayer* MyStructPlayer = Cast<AMyStructPlayer>(MyPlayer);

		if (MyStructPlayer != nullptr)
		{
			FMyStruct Player;
			Player.Name = MyStructPlayer->Name;
			Player.Health = MyStructPlayer->Health;

			Players.Add(Player);
		}
	}
}

TArray<AActor*> AMyStructBoundingBox::SetPlayersActors()
{
	TArray<AActor*> OutOverlappingActors;
	Box->GetOverlappingActors(OutOverlappingActors, AMyStructPlayer::StaticClass());

	return OutOverlappingActors;
}
