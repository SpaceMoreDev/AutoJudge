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
	void InputSprint(const FInputActionValue& Value);

	UFUNCTION(BlueprintImplementableEvent)
	void PlayerFire(float DamageGiven);

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
	UPROPERTY(EditDefaultsOnly, Category = "Control")
	UInputAction* SprintInput;

	float LeanDirection = 0.f;
	float Speed = 20;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float SprintSpeed = 1000;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float WalkSpeed = 500;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float LookSpeed = 10;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float LookLimit = 70.f;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float LeanForce = 15.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Aim Settings")
	float SelectionRange = 500.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Aim Settings")
	float FireDamage = 100.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Aim Settings")
	class UNiagaraSystem* fireParticle;

	UPROPERTY(EditAnywhere)
	class UCameraComponent* playerCamera;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UCharacterMovementComponent* MovementComp;
	UPROPERTY(EditDefaultsOnly)
	class UCapsuleComponent* CapsuleComp;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UCameraShakeBase> cameraShake;

};
