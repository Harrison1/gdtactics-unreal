// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "TP_ThirdPersonCharacter.generated.h"

class ATP_FirstPersonCharacter;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateThirdPersonCharacter, Log, All);

UCLASS(config=Game)
class ATP_ThirdPersonCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* InputMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	/** Sprint Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SprintAction;

	/** Toggle Character Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ToggleCharacterAction;

	/** Toggle Time Dilation Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ToggleTimeDilationAction;

public:
	ATP_ThirdPersonCharacter();
	

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	/** Called for sprinting input */
	void Sprint(const FInputActionValue& Value);

	/** Called for the toggle character input */
	void ToggleCharacter(const FInputActionValue& Value);

	/** Called for the toggle time dilation input */
	void ToggleTimeDilation(const FInputActionValue& Value);
	
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

	// Perform when possessed or unpossessed during the toggle character feature
	virtual void PossessedBy(AController* NewController) override;
	virtual void UnPossessed() override;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UFUNCTION(BlueprintCallable)
	void StartCoyoteTimer();
	
	UFUNCTION(BlueprintCallable)
	void DisableCoyoteTime();
	
	UPROPERTY()
	bool bCanCoyoteJump = false;

	UPROPERTY()
	bool bIsTimeDilated = false;
	
	UPROPERTY(EditAnywhere)
	float CoyoteTime = 0.33f;

	UPROPERTY(EditAnywhere)
	FTimerHandle CoyoteTimerHandle;

	// Subclass used for the toggle character feature
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "First Person Character Toggle")
	TSubclassOf<class ATP_FirstPersonCharacter> MyFirstPersonCharacterSubClass;

	// Actor used for the toggle character feature
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "First Person Character Toggle")
	ATP_FirstPersonCharacter* MyFirstPersonCharacter;

	/** Sound to play each time we toggle characters */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "First Person Character Toggle")
	USoundBase* ToggleSound;
	
	virtual void Falling() override;
	virtual bool CanJumpInternal_Implementation() const override;
	virtual void OnJumped_Implementation() override;
	virtual void OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode = 0) override;
};

