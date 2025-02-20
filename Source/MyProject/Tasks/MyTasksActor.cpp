#include "MyTasksActor.h"


// Sets default values
AMyTasksActor::AMyTasksActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("MyRoot"));
#if WITH_EDITORONLY_DATA
	MyRoot->bVisualizeComponent = true;
#endif
	RootComponent = MyRoot;
}

// Called when the game starts or when spawned
void AMyTasksActor::BeginPlay()
{
	Super::BeginPlay();

	{
		using namespace UE::Tasks;
		
		FTask A = Launch(UE_SOURCE_LOCATION, [this]{ FunctionA(); });
		FTask B = Launch(UE_SOURCE_LOCATION, [this]{ FunctionB(); }, A);
		FTask C = Launch(UE_SOURCE_LOCATION, [this]{ FunctionC(); }, B);
		FTask D = Launch(UE_SOURCE_LOCATION, [this]{ FunctionD(); }, Prerequisites(B, C));

		constexpr int32 MyTime = 3;
		bool bAllTasksComplete = D.Wait(FTimespan::FromSeconds(MyTime));

		if (bAllTasksComplete)
		{
			UE_LOG(LogTemp, Warning, TEXT("All Tasks completed within %d seconds"), MyTime);
		}
	}
}

void AMyTasksActor::FunctionA()
{
	UE_LOG(LogTemp, Warning, TEXT("Task A is complete!!!"));
}

void AMyTasksActor::FunctionB()
{
	UE_LOG(LogTemp, Warning, TEXT("Task B is complete!!!"));
}

void AMyTasksActor::FunctionC()
{
	UE_LOG(LogTemp, Warning, TEXT("Task C is complete!!!"));
}

void AMyTasksActor::FunctionD()
{
	UE_LOG(LogTemp, Warning, TEXT("Task D is complete!!!"));
}
