#include "MyCameraShake.h"
#include "Shakes/PerlinNoiseCameraShakePattern.h"

// Sets default values
UMyCameraShake::UMyCameraShake()
	: UCameraShakeBase(FObjectInitializer::Get())
{
	// only play if not playing already
	bSingleInstance = true;
	
	UPerlinNoiseCameraShakePattern* MyPerlinPattern = CreateDefaultSubobject<UPerlinNoiseCameraShakePattern>(TEXT("MyPerlinPattern"));
	
	MyPerlinPattern->X.Amplitude = 10.f;
	MyPerlinPattern->X.Frequency = 10.f;
	MyPerlinPattern->Y.Amplitude = 10.f;
	MyPerlinPattern->Y.Frequency = 10.f;
	MyPerlinPattern->Z.Amplitude = 10.f;
	MyPerlinPattern->Z.Frequency = 10.f;

	MyPerlinPattern->Pitch.Amplitude = 10.f;
	MyPerlinPattern->Pitch.Frequency = 10.f;
	MyPerlinPattern->Yaw.Amplitude = 10.f;
	MyPerlinPattern->Yaw.Frequency = 10.f;
	MyPerlinPattern->Roll.Amplitude = 10.f;
	MyPerlinPattern->Roll.Frequency = 10.f;

	MyPerlinPattern->FOV.Amplitude = 10.f;
	MyPerlinPattern->FOV.Frequency = 10.f;

	MyPerlinPattern->Duration = 2.f;

	SetRootShakePattern(MyPerlinPattern);
}
