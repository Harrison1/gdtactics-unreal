#include "MyHelpers.h"
#include "Kismet/KismetMathLibrary.h"

FVector UMyHelpers::AimAheadLocation(FVector ActorLocation, float ProjectileSpeed, FVector TargetLocation, FVector TargetVelocity)
{
	/** Helpful variables to assist with A, B, and C */
	const FVector LocationDelta = TargetLocation - ActorLocation;
	const float VelocityDot = FVector::DotProduct(TargetVelocity, TargetVelocity);
	const float SpeedSqrd = FMath::Pow(ProjectileSpeed, 2.0f);
	
	/** Create A, B, and C for the Quadratic Formula */
	const float A = SpeedSqrd - VelocityDot; // Speed Delta
	const float B = 2.f * FVector::DotProduct(TargetVelocity, LocationDelta);
	const float C = FVector::DotProduct(LocationDelta, LocationDelta);
	const float D = B*B + 4.f*A*C; // Discriminant (using addition rather than subtraction to negate negative values)

	/**
	 * Solve the Quadratic Formula
	 * We only need the positive root result
	 * Using B instead of -B to negate negative values
	 *
	 * Notes
	 * Use -B if LocationDelta equals TargetLocation - ActorLocation
	 * Use subtraction in the Discriminant if A = VeclocityDot - SpeedSqrd
	 * Use FMath::Abs(T) (abs) when using the above two statements
	 */
	if (D >= 0.f)
	{
		const float T = (B + FMath::Sqrt(D)) / (2.f*A);

		const FVector AimLocation = TargetLocation + (TargetVelocity * T);

		return AimLocation;
	}
	
	return TargetLocation;
}

FRotator UMyHelpers::LookAtAimAheadLocation(FVector ActorLocation, float ProjectileSpeed, FVector TargetLocation, FVector TargetVelocity)
{

	FVector AimLocation = AimAheadLocation(ActorLocation, ProjectileSpeed, TargetLocation, TargetVelocity);

	return UKismetMathLibrary::FindLookAtRotation(ActorLocation, AimLocation);
}
