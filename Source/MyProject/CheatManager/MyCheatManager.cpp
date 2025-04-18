#include "MyCheatManager.h"
#include "MyProject/TP_ThirdPerson/TP_ThirdPersonCharacter.h"

UMyCheatManager::UMyCheatManager()
{
	static IConsoleCommand* MyConsleCommand = IConsoleManager::Get().RegisterConsoleCommand(
		TEXT("MyCheatManager.PrintCommand"),
		TEXT("Print a simle string from the MyCheatManager"),
		FConsoleCommandWithWorldAndArgsDelegate::CreateLambda(&UMyCheatManager::MyCommandFunction),
		ECVF_Cheat
	);
}

void UMyCheatManager::GetPlayerName()
{
	AActor* MyActor = GetWorld()->GetFirstPlayerController()->GetPawn();
	ATP_ThirdPersonCharacter* MyCharacter = Cast<ATP_ThirdPersonCharacter>(MyActor);

	if (MyCharacter != nullptr)
	{
		FString PlayerName = MyCharacter->GetName();
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, *FString::Printf(TEXT("Character Name: %s"), *PlayerName));
		}
	}
}

static FAutoConsoleCommandWithWorldAndArgs TestCommand(
	TEXT("MyCheatManager.TestCommand"),
	TEXT("Test Command in MyCheatManager"),
	FConsoleCommandWithWorldAndArgsDelegate::CreateStatic([](const TArray<FString>& Params, UWorld* World)
	{
		if (Params.Num() == 0)
		{
			UE_LOG(LogTemp, Log, TEXT("No params listed"));
		}

		for (const FString& Param : Params)
		{
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, *FString::Printf(TEXT("Param Name: %s"), *Param));
			}
		}
	}),
	ECVF_Cheat
);

void UMyCheatManager::MyCommandFunction(const TArray<FString>& Args, UWorld* World)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 105.f, FColor::Green, TEXT("IConsole Command"));
	}
}
