// Copyright Epic Games, Inc. All Rights Reserved.

#include "TP_FirstPersonCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"
#include "MyProject/TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY(LogTemplateFirstPersonCharacter);

//////////////////////////////////////////////////////////////////////////
// ATP_FirstPersonCharacter

ATP_FirstPersonCharacter::ATP_FirstPersonCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

}

void ATP_FirstPersonCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
}

void ATP_FirstPersonCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			if (Subsystem->HasMappingContext(InputMappingContext))
			{
				Subsystem->AddMappingContext(InputMappingContext, 0);	
			}
		}
	}
	
	GetCapsuleComponent()->SetVisibility(true, true);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void ATP_FirstPersonCharacter::UnPossessed()
{
	Super::UnPossessed();
	GetCapsuleComponent()->SetVisibility(false, true);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

//////////////////////////////////////////////////////////////////////////// Input

void ATP_FirstPersonCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}
	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATP_FirstPersonCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATP_FirstPersonCharacter::Look);

		// Toggle Character
		EnhancedInputComponent->BindAction(ToggleCharacterAction, ETriggerEvent::Triggered, this, &ATP_FirstPersonCharacter::ToggleCharacter);
	}
	else
	{
		UE_LOG(LogTemplateFirstPersonCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}


void ATP_FirstPersonCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void ATP_FirstPersonCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ATP_FirstPersonCharacter::ToggleCharacter(const FInputActionValue& Value)
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	
	if (PlayerController != nullptr)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->RemoveMappingContext(InputMappingContext);
		}
	}

	// play the toggle sound if specified
	if (ToggleSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, ToggleSound, GetActorLocation());
	}

	if (MyThirdPersonCharacter != nullptr && PlayerController != nullptr)
	{
		MyThirdPersonCharacter->SetActorTransform(GetActorTransform());
		PlayerController->Possess(MyThirdPersonCharacter);
	}
	else if (MyThirdPersonCharacterSubClass != nullptr && PlayerController != nullptr)
	{
		if (UWorld* const World = GetWorld())
		{
			AActor* MyNewCharacter = UGameplayStatics::GetActorOfClass(World, MyThirdPersonCharacterSubClass);
			// ATP_FirstPersonCharacter* MyNewCharacter = Cast<ATP_FirstPersonCharacter>(UGameplayStatics::GetActorOfClass(World, MyFirstPersonCharacterSubClass));
			
			if (MyNewCharacter == nullptr)
			{
				FActorSpawnParameters ActorSpawnParams;
				ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

				MyThirdPersonCharacter = World->SpawnActor<ATP_ThirdPersonCharacter>(MyThirdPersonCharacterSubClass, GetActorTransform(), ActorSpawnParams);
				if (MyThirdPersonCharacter != nullptr)
				{
					PlayerController->Possess(MyThirdPersonCharacter);	
				}
			}
			else
			{
				ATP_ThirdPersonCharacter* MyPossessCharacter = Cast<ATP_ThirdPersonCharacter>(MyNewCharacter);
				if (MyPossessCharacter != nullptr)
				{
					MyPossessCharacter->SetActorTransform(GetActorTransform());
					PlayerController->Possess(MyPossessCharacter);	
				}
			}
		}
	}
}
