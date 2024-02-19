// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/PlayerController.h"
#include "Camera/CameraShakeBase.h"
// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	playerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	playerCamera->SetupAttachment(RootComponent);
	playerCamera->AddLocalOffset(FVector(0.f, 0.f, 70.f));
	MovementComp = Super::GetCharacterMovement();
	CapsuleComp = Super::GetCapsuleComponent();

	MovementComp->JumpZVelocity = 600.0f*2.f;
	MovementComp->GravityScale = 2.89f;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		// Get the Enhanced Input Local Player Subsystem from the Local Player related to our Player Controller.
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(inputMap, 0);
			UE_LOG(LogTemp, Warning, TEXT("Input Context Setup Complete"));
		}
	}
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Lean(LeanDirection);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//PlayerInputComponent->BindAction("Movement", IE_Released, this, &APlayerCharacter::InputMove);

	UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	enhancedInputComponent->BindAction(movementInput, ETriggerEvent::Triggered, this, &APlayerCharacter::InputMove);
	enhancedInputComponent->BindAction(movementInput, ETriggerEvent::Completed, this, &APlayerCharacter::InputMove);

	enhancedInputComponent->BindAction(lookInput, ETriggerEvent::Triggered, this, &APlayerCharacter::InputLook);
	enhancedInputComponent->BindAction(JumpInput, ETriggerEvent::Triggered, this, &APlayerCharacter::InputJump);
}

void APlayerCharacter::Lean(float dir)
{
	FRotator current = playerCamera->GetComponentRotation();
	float newRoll = UKismetMathLibrary::FInterpTo(current.Roll, (dir * LeanForce), GetWorld()->GetDeltaSeconds(), 4.0f);
	playerCamera->SetRelativeRotation(FRotator(0.f, 0.f, newRoll));
}

void APlayerCharacter::HeadBobbing(float velocity)
{
	//FMath.SinCos();
}

void APlayerCharacter::InputMove(const FInputActionValue& Value)
{
	FVector2D dir = Value.Get<FVector2D>();
	LeanDirection = dir.X;
	if (dir.Length()>0)
	{
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(cameraShake);
	}
	else {
		GetWorld()->GetFirstPlayerController()->ClientStopCameraShake(cameraShake);
	}
	
	AddMovementInput(playerCamera->GetRightVector(), dir.X * Speed);
	AddMovementInput(playerCamera->GetForwardVector(), dir.Y * Speed);
}
void APlayerCharacter::InputLook(const FInputActionValue& Value)
{
	FVector2D dir = Value.Get<FVector2D>();

	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	if (PlayerController)
	{
		if (PlayerController->PlayerCameraManager)
		{
			PlayerController->PlayerCameraManager->ViewPitchMin = -LookLimit;
			PlayerController->PlayerCameraManager->ViewPitchMax = LookLimit;
		}
	}

	AddControllerYawInput(dir.X * LookSpeed * GetWorld()->GetDeltaSeconds());
	AddControllerPitchInput(-dir.Y * LookSpeed * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::InputJump(const FInputActionValue& Value)
{
	Jump();
}


