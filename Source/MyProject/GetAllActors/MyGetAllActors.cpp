#include "MyGetAllActors.h"

#include "EngineUtils.h"
#include "TestActor.h"
#include "TestActorInt.h"
#include "MyProject/Interfaces/MyInterface.h"
#include "Kismet/GameplayStatics.h"

AMyGetAllActors::AMyGetAllActors()
{
	PrimaryActorTick.bCanEverTick = false;

	MySceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("MySceneComponent"));
#if WITH_EDITORONLY_DATA
	MySceneComponent->bVisualizeComponent = true;
#endif
	RootComponent = MySceneComponent;

	ByClass = CreateDefaultSubobject<UMyStatObject>(TEXT("ByClass"));
	ByClassInt = CreateDefaultSubobject<UMyStatObject>(TEXT("ByClassInt"));
	ByInterface = CreateDefaultSubobject<UMyStatObject>(TEXT("ByInterface"));
	ByTag = CreateDefaultSubobject<UMyStatObject>(TEXT("ByTag"));
	ByRange = CreateDefaultSubobject<UMyStatObject>(TEXT("ByRange"));
	ByIterator = CreateDefaultSubobject<UMyStatObject>(TEXT("ByIterator"));
	
	ByClass->MyStats.FunctionName = TEXT("GetAllActorsOfClass (All Actors)");
	ByClassInt->MyStats.FunctionName = TEXT("GetAllActorsOfClass (Only TestInt Actors)");
	ByInterface->MyStats.FunctionName = TEXT("GetAllActorsWithInterface");
	ByTag->MyStats.FunctionName = TEXT("GetAllActorsWithTag");
	ByRange->MyStats.FunctionName = TEXT("TActorRange");
	ByIterator->MyStats.FunctionName = TEXT("TActorIterator");
	
	StatMap.Add(1, ByClass);
	StatMap.Add(2, ByClassInt);
	StatMap.Add(3, ByInterface);
	StatMap.Add(4, ByTag);
	StatMap.Add(5, ByRange);
	StatMap.Add(6, ByIterator);
}

void AMyGetAllActors::BeginPlay()
{
	Super::BeginPlay();

	MyWorld = GetWorld();
	
	SpawnTestActors();

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AMyGetAllActors::TestGetAll, 6.f, true, 0.f);

	FTimerHandle TimerHandle2;
	GetWorldTimerManager().SetTimer(TimerHandle2, this, &AMyGetAllActors::TestGetAllTestInt, 6.f, true, 1.f);
	
	FTimerHandle TimerHandle3;
	GetWorldTimerManager().SetTimer(TimerHandle3, this, &AMyGetAllActors::TestGetAllWithInterface, 6.f, true, 2.f);
	
	FTimerHandle TimerHandle4;
	GetWorldTimerManager().SetTimer(TimerHandle4, this, &AMyGetAllActors::TestGetAllWithTag, 6.f, true, 3.f);
	
	FTimerHandle TimerHandle5;
	GetWorldTimerManager().SetTimer(TimerHandle5, this, &AMyGetAllActors::TestGetAllWithRange, 6.f, true, 4.f);
	
	FTimerHandle TimerHandle6;
	GetWorldTimerManager().SetTimer(TimerHandle6, this, &AMyGetAllActors::TestGetAllWithIterator, 6.f, true, 5.f);
}

void AMyGetAllActors::SpawnTestActors() const
{
	if (UWorld* const World = GetWorld())
	{
		float X = 0.f;
		float Y = 0.f;

		for (int i = 0; i < SpawnAmount; i++)
		{
			X += 150.f;
			
			if (i % 100 == 0)
			{
				X = 0;
				Y += 150;
			}
			
			const FVector SpawnLocation = FVector(X, Y, 100.f);
			
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			if (FMath::RandBool())
			{
				World->SpawnActor<ATestActor>(ATestActor::StaticClass(), SpawnLocation, FRotator::ZeroRotator, ActorSpawnParams);
			}
			else
			{
				World->SpawnActor<ATestActorInt>(ATestActorInt::StaticClass(), SpawnLocation, FRotator::ZeroRotator, ActorSpawnParams);
			}
		}
	}
}

void AMyGetAllActors::TestGetAll()
{
	QUICK_SCOPE_CYCLE_COUNTER(MyStat_GetAllActorsOfClass);

	double ThisTimeClass = 0;
	TArray<AActor*> FoundActors;
	if (MyWorld != nullptr)
	{
		SCOPE_SECONDS_COUNTER(ThisTimeClass);
		
		UGameplayStatics::GetAllActorsOfClass(MyWorld, AActor::StaticClass(), FoundActors);
	}
	UMyStatObject* ClassObject = StatMap.FindChecked(1);
	ClassObject->MyStats.Time = ThisTimeClass;
	ClassObject->MyStats.Total = FoundActors.Num();

	LogAndCompare(TEXT("Class"), ThisTimeClass, ClassObject->MyStats.Total);
}

void AMyGetAllActors::TestGetAllTestInt()
{
	QUICK_SCOPE_CYCLE_COUNTER(MyStat_GetAllActorsOfClassInt);

	double ThisTimeClassInt = 0;
	TArray<AActor*> FoundActorsOfTestInt;
	if (MyWorld != nullptr)
	{
		SCOPE_SECONDS_COUNTER(ThisTimeClassInt);
		
		UGameplayStatics::GetAllActorsOfClass(MyWorld, ATestActorInt::StaticClass(), FoundActorsOfTestInt);

		for (AActor* Actor : FoundActorsOfTestInt)
		{
			if (IsValid(Actor) && Actor->Implements<UMyInterface>())
			{
				// do work if actor implements interfacee
			}
		}
	}
	UMyStatObject* ClassIntObject = StatMap.FindChecked(2);
	ClassIntObject->MyStats.Time = ThisTimeClassInt;
	ClassIntObject->MyStats.Total = FoundActorsOfTestInt.Num();

	LogAndCompare(TEXT("Class TestActorInt"), ThisTimeClassInt, ClassIntObject->MyStats.Total);
}

void AMyGetAllActors::TestGetAllWithInterface()
{
	QUICK_SCOPE_CYCLE_COUNTER(MyStat_GetAllActorsWithInterface);

	double ThisTimeInterface = 0;
	TArray<AActor*> FoundActorsInterface;
	if (MyWorld != nullptr)
	{
		SCOPE_SECONDS_COUNTER(ThisTimeInterface);
		
		UGameplayStatics::GetAllActorsWithInterface(MyWorld, UMyInterface::StaticClass(), FoundActorsInterface);
	}
	UMyStatObject* InterfaceObject = StatMap.FindChecked(3);
	InterfaceObject->MyStats.Time = ThisTimeInterface;
	InterfaceObject->MyStats.Total = FoundActorsInterface.Num();

	LogAndCompare(TEXT("Interface"), ThisTimeInterface, InterfaceObject->MyStats.Total);
}

void AMyGetAllActors::TestGetAllWithTag()
{
	QUICK_SCOPE_CYCLE_COUNTER(MyStat_GetAllActorsWithTag);

	double ThisTimeTag = 0;
	TArray<AActor*> FoundActorsTag;
	if (MyWorld != nullptr)
	{
		SCOPE_SECONDS_COUNTER(ThisTimeTag);
		
		UGameplayStatics::GetAllActorsWithTag(MyWorld,  TEXT("MyTag"), FoundActorsTag);
	}
	UMyStatObject* TagObject = StatMap.FindChecked(4);
	TagObject->MyStats.Time = ThisTimeTag;
	TagObject->MyStats.Total = FoundActorsTag.Num();
	
	LogAndCompare(TEXT("Tag"), ThisTimeTag, TagObject->MyStats.Total);
}

void AMyGetAllActors::TestGetAllWithRange()
{
	QUICK_SCOPE_CYCLE_COUNTER(MyStat_GetAllActorsWithRange);

	double ThisTimeRange = 0;
	TArray<AActor*> FoundActorsRange;
	if (MyWorld != nullptr)
	{
		SCOPE_SECONDS_COUNTER(ThisTimeRange);
		
		for (AActor* Actor : TActorRange<AActor>(MyWorld))
		{
			FoundActorsRange.Add(Actor);
		}
	}
	UMyStatObject* RangeObject = StatMap.FindChecked(5);
	RangeObject->MyStats.Time = ThisTimeRange;
	RangeObject->MyStats.Total = FoundActorsRange.Num();
	
	LogAndCompare(TEXT("Range Loop"), ThisTimeRange, RangeObject->MyStats.Total);
}

void AMyGetAllActors::TestGetAllWithIterator()
{
	QUICK_SCOPE_CYCLE_COUNTER(MyStat_GetAllActorsWithRange);

	double ThisTimeIterator = 0;
	TArray<AActor*> FoundActorsIterator;
	if (MyWorld != nullptr)
	{
		SCOPE_SECONDS_COUNTER(ThisTimeIterator);

		for (TActorIterator<AActor> It(MyWorld); It; ++It)
		{
			FoundActorsIterator.Add(*It);
		}
	}
	UMyStatObject* IteratorObject = StatMap.FindChecked(6);
	IteratorObject->MyStats.Time = ThisTimeIterator;
	IteratorObject->MyStats.Total = FoundActorsIterator.Num();
	
	LogAndCompare(TEXT("Iterator Loop"), ThisTimeIterator, IteratorObject->MyStats.Total);
}

void AMyGetAllActors::LogAndCompare(const FString& GetAllMethod, const double Time, const int32 TotalActors)
{
	UE_LOG(LogTemp, Log, TEXT("GetAll By %s: %.8f, TotalActors: %d"), *GetAllMethod, Time, TotalActors);
	CompareTime();
}


void AMyGetAllActors::CompareTime()
{
	StatMap.ValueSort([](const UMyStatObject& A, const UMyStatObject& B) {
		return A.MyStats.Time < B.MyStats.Time;
	});

	TArray<UMyStatObject*> StatArray;
	StatMap.GenerateValueArray(StatArray);
	
	UpdateStatArray.Broadcast(StatArray);
}
