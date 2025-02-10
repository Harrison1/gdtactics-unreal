#include "MyPlayerController.h"
#include "MyProject/CheatManager/MyCheatManager.h"

AMyPlayerController::AMyPlayerController()
{
	CheatClass = UMyCheatManager::StaticClass();
}
