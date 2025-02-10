#include "MyCheatManager.h"
#include "MyProject/TP_ThirdPerson/TP_ThirdPersonCharacter.h"

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
