#include "MyStructPlayer.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/WidgetComponent.h"

// Sets default values
AMyStructPlayer::AMyStructPlayer()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Root->bVisualizeComponent = true;
	RootComponent = Root;

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMesh->SetupAttachment(RootComponent);

	Widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	Widget->SetupAttachment(RootComponent);
}

void AMyStructPlayer::BeginPlay()
{
	Super::BeginPlay();

	if (Widget != nullptr)
	{
		
	}
}
