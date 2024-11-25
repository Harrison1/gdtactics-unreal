#include "MyStructActor.h"
#include "MyStructPlayer.h"
#include "Components/BoxComponent.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "MyProject/Widgets/MyWidget_List.h"

// Sets default values
AMyStructActor::AMyStructActor()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Root->bVisualizeComponent = true;
	RootComponent = Root;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box->SetHiddenInGame(false);
	Box->SetupAttachment(RootComponent);
	
	// Box->OnComponentBeginOverlap.AddDynamic(this, &AMyStructActor::OnBeginOverlap);
	// Box->OnComponentEndOverlap.AddDynamic(this, &AMyStructActor::OnEndOverlap);
}

void AMyStructActor::SetPlayers()
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

TArray<AActor*> AMyStructActor::SetPlayersActors()
{
	TArray<AActor*> OutOverlappingActors;
	Box->GetOverlappingActors(OutOverlappingActors, AMyStructPlayer::StaticClass());

	return OutOverlappingActors;
}

// void AMyStructActor::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
// {
// 	TArray<AActor*> OutOverlappingActors;
// 	Box->GetOverlappingActors(OutOverlappingActors, AMyStructPlayer::StaticClass());
//
// 	for (AActor* MyPlayer : OutOverlappingActors)
// 	{
// 		AMyStructPlayer* MyStructPlayer = Cast<AMyStructPlayer>(MyPlayer);
//
// 		if (MyStructPlayer != nullptr)
// 		{
// 			FMyStruct Player;
// 			Player.Name = MyStructPlayer->Name;
// 			Player.Health = MyStructPlayer->Health;
//
// 			Players.Add(Player);
//
// 			UE_LOG(LogTemp, Warning, TEXT("Player here"));
// 		}
// 	}
//
// 	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
//
// 	if (PlayerController != nullptr)
// 	{
// 		MyUserWidgetList = CreateWidget<UMyWidget_List>(PlayerController, UMyWidget_List::StaticClass(), TEXT("MyUserWidgetList"));
//
// 		if (MyUserWidgetList != nullptr)
// 		{
// 			UE_LOG(LogTemp, Display, TEXT("Hello Widget Viewport"));
// 			MyUserWidgetList->AddToViewport();
// 		}	
// 	}
// }
//
// void AMyStructActor::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
// {
// 	MyUserWidgetList->RemoveFromParent();
// }
