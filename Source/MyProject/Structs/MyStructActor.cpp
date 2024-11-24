#include "MyStructActor.h"
#include "MyStructPlayer.h"
#include "Blueprint/UserWidget.h"
#include "Components/BoxComponent.h"

// Sets default values
AMyStructActor::AMyStructActor()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Root->bVisualizeComponent = true;
	RootComponent = Root;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box->SetHiddenInGame(false);
	Box->SetupAttachment(RootComponent);
	
	Box->OnComponentBeginOverlap.AddDynamic(this, &AMyStructActor::OnBeginOverlap);
	Box->OnComponentEndOverlap.AddDynamic(this, &AMyStructActor::OnEndOverlap);
}

void AMyStructActor::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
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

	// MyUserWidget = CreateWidget(this, UUserWidget::StaticClass(), TEXT("MyUserWidget"));
	//
	// MyUserWidget->AddToViewport();
}

void AMyStructActor::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// MyUserWidget->RemoveFromParent();
}
