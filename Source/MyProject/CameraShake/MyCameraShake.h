#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraShakeBase.h"
#include "MyCameraShake.generated.h"


UCLASS()
class MYPROJECT_API UMyCameraShake : public UCameraShakeBase
{
	GENERATED_BODY()

public:
	// Constructor, set up and set defaults for the camera shake
	UMyCameraShake();
};
