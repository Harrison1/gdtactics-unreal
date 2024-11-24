#include "MyStructPlayer.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "MyProject/Widgets/MyWidget_Health.h"

// Sets default values
AMyStructPlayer::AMyStructPlayer()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Root->bVisualizeComponent = true;
	RootComponent = Root;

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMesh->SetupAttachment(RootComponent);

	Widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	Widget->SetWidgetClass(UMyWidget_Health::StaticClass());
	Widget->SetupAttachment(RootComponent);

	MyStruct.Name = TEXT("Name");
	MyStruct.Health = 100;
}

void AMyStructPlayer::BeginPlay()
{
	Super::BeginPlay();

	if (Widget != nullptr && Widget->GetWidgetClass() != nullptr)
	{
		UUserWidget* UserWidgetObject = Widget->GetUserWidgetObject();
		if (UserWidgetObject != nullptr)
		{
			UMyWidget_Health* MyHealthWidget = Cast<UMyWidget_Health>(UserWidgetObject);

			if (MyHealthWidget != nullptr)
			{
				MyHealthWidget->SetName(MyStruct.Name);
				MyHealthWidget->SetHealth(MyStruct.Health);
			}
		}
	}
}
