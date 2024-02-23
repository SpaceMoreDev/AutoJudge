// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class AUTOJUDGE_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly,Category = "Combat")
	class UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* MovementComponent;

	UPROPERTY(EditAnywhere)
	float Damage = 50.f;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherHitComp, FVector ImppactPos, const FHitResult &Hit);

	UPROPERTY(EditAnywhere, Category = "Combat");
	class UNiagaraSystem* HitParticle;

	UPROPERTY(EditAnywhere, Category = "Combat");
	class USoundBase* LaunchSound;

	UPROPERTY(EditAnywhere, Category = "Combat");
	class USoundBase* HitSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projectile Settings")
	class UNiagaraComponent* TrailParticle;

	UPROPERTY(EditAnywhere, Category = "Combat");
	TSubclassOf< class UCameraShakeBase> HitCameraShakeclass;
};
