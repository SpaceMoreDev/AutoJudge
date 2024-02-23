// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NPCCharacter.generated.h"


UCLASS()
class AUTOJUDGE_API ANPCCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANPCCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent)
	void StartAI();

	void FireBullet();

	UPROPERTY(EditDefaultsOnly)
	class USkeletalMeshComponent* npcMesh;

	class APlayerCharacter* player;

	UPROPERTY(EditAnywhere)
	float MoveSpeed = 500.f;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AProjectile> Projectile;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	class USceneComponent* ShootingPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	double shootIntervals = 0.2;

	bool canShoot = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	double shootRange = 2000.0;

	FTimerHandle SpawnRateTimerHandle;
};
