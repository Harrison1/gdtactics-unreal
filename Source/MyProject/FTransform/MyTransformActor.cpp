#include "MyTransformActor.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
AMyTransformActor::AMyTransformActor()
{
	// sets location, rotation defaults to FQuat::Identity and scale defaults to FVector(1)
	FTransform MyTransform1(FVector::ZeroVector);

	// sets rotation, FRotator or FQuat should suffice, location defaults to FVector::ZeroVector and scale defaults to FVector(1)
	FTransform MyTransform2(FQuat::Identity);

	// set all three parameters. Rotation as a Quaternion comes first.
	FTransform MyTransform3(FQuat::Identity, FVector::ZeroVector, FVector(1));

	// set using FTransform setters
	FTransform MyTransformSet;
	MyTransformSet.SetLocation(GetActorLocation());
	MyTransformSet.SetRotation(GetActorRotation().Quaternion()); // Alternatively FQuat(GetActorRotation)
	MyTransformSet.SetScale3D(FVector(1, 1, 1));

	// create a transform using the UKismetMathLibrary library.
	FVector MyLocation = GetActorLocation();
	FRotator MyRotator = GetActorRotation();
	FVector MyScale = FVector(1);
	FTransform MyTransformLib = UKismetMathLibrary::MakeTransform(MyLocation, MyRotator, MyScale);
}
