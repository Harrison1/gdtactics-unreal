#include "MyCast.h"
#include "Components/BoxComponent.h"
#include "MyProject/TP_FirstPerson/TP_FirstPersonCharacter.h"
#include "MyProject/TP_ThirdPerson/TP_ThirdPersonCharacter.h"


// Sets default values
AMyCast::AMyCast()
{
	MyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("MyRoot"));
	MyRoot->bVisualizeComponent = true;
	RootComponent = MyRoot;

	MyBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("MyBoxComponent"));
	MyBoxComponent->SetupAttachment(RootComponent);

	MyBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AMyCast::OnBeginOverlap);
}

// Called when the game starts or when spawned
void AMyCast::BeginPlay()
{
	Super::BeginPlay();

	// we first get the pawn as type AActor for a general class. Instead of AActor we can use APawn.
	AActor* MyActor = GetWorld()->GetFirstPlayerController()->GetPawn();
	ATP_ThirdPersonCharacter* MyCharacter = Cast<ATP_ThirdPersonCharacter>(MyActor);

	// check if cast was successful
	if (MyCharacter != nullptr)
	{
		// we can now act upon on MyCharacter variable
		UE_LOG(LogTemp, Display, TEXT("Cast successful"));
		
		// MyCharacter->CharacterFunction();
	}
	else
	{
		// Cast failed
		UE_LOG(LogTemp, Warning, TEXT("Cast failed"));
	}

	APawn* MyPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	// CastChecked if you're certain the cast won't fail
	ATP_ThirdPersonCharacter* MyCharacterChecked = CastChecked<ATP_ThirdPersonCharacter>(MyPawn);
	// MyCharacterChecked->CharacterFunction();
}

void AMyCast::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr && OtherActor != this)
	{
		ATP_FirstPersonCharacter* MyFirstPersonCharacter = Cast<ATP_FirstPersonCharacter>(OtherActor);

		if (MyFirstPersonCharacter)
		{
			// MyFirstPersonCharacter->MyFunction();
		}
	}
}
