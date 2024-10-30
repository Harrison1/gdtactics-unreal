#include "MyBlueprintFunctionLibrary.h"
#include "Kismet/KismetMathLibrary.h"

bool UMyBlueprintFunctionLibrary::IsActorInFront(FVector ActorLocation, FVector OtherActorLocation, FRotator OtherActorRotation)
{
	FVector NewLocation = ActorLocation - OtherActorLocation;
	FVector UnrotatedVector = OtherActorRotation.UnrotateVector(NewLocation);
	
	return UnrotatedVector.X > 0 ? true : false;
}

FRotator UMyBlueprintFunctionLibrary::GetRotateValue(FRotator ActorRotation, float Alpha, bool OpenDirection, float RotateDegrees)
{
	float Direction = OpenDirection ? RotateDegrees : -RotateDegrees;
	FRotator NewRotation = FRotator(0.0f, Direction, 0.0f);
	FRotator FinalRotation = UKismetMathLibrary::RLerp(ActorRotation, NewRotation, Alpha, true);

	return FinalRotation;
}
