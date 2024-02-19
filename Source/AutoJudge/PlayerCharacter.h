// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class AUTOJUDGE_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Lean(float direction);
	void InputMove(const FInputActionValue& Value);
	void InputLook(const FInputActionValue& Value);
	void InputJump(const FInputActionValue& Value);
	void InputFire(const FInputActionValue& Value);

	UFUNCTION(BlueprintImplementableEvent)
	void PlayerFire();

	UPROPERTY(EditDefaultsOnly, Category = "Control")
	UInputMappingContext* inputMap;
	UPROPERTY(EditDefaultsOnly, Category = "Control")
	UInputAction* movementInput;
	UPROPERTY(EditDefaultsOnly, Category = "Control")
	UInputAction* lookInput;
	UPROPERTY(EditDefaultsOnly, Category = "Control")
	UInputAction* JumpInput;
	UPROPERTY(EditDefaultsOnly, Category = "Control")
	UInputAction* FireInput;

	float LeanDirection = 0.f;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float Speed = 20;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float LookSpeed = 10;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float LookLimit = 70.f;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float LeanForce = 15.f;

	UPROPERTY(EditAnywhere)
	class UCameraComponent* playerCamera;
	UPROPERTY(EditDefaultsOnly)
	class UCharacterMovementComponent* MovementComp;
	UPROPERTY(EditDefaultsOnly)
	class UCapsuleComponent* CapsuleComp;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UCameraShakeBase> cameraShake;

};
