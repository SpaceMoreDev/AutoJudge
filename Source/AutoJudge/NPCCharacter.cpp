// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCCharacter.h"
#include "PlayerCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "AIController.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TimerManager.h"
#include "Projectile.h"

// Sets default values
ANPCCharacter::ANPCCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	npcMesh = Super::GetMesh();

	ShootingPoint = CreateDefaultSubobject<USceneComponent>(TEXT("BulletPoint"));
	ShootingPoint->SetupAttachment(RootComponent);

	Super::GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;

	


}

// Called when the game starts or when spawned
void ANPCCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(SpawnRateTimerHandle, this, &ANPCCharacter::FireBullet, shootIntervals, true);
	//SpawnDefaultController();
	player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (player != NULL)
	{
		StartAI();
	}
	//
}

// Called every frame
void ANPCCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (player != NULL && !cutscene)
	{

		FHitResult hit;

		FVector Start = GetActorLocation();

		GetWorld()->LineTraceSingleByChannel(hit, Start, player->GetActorLocation(), ECollisionChannel::ECC_Visibility);
		//DrawDebugLine(GetWorld(), Start, player->GetActorLocation(), FColor::Red, false, 0.2f);
		APlayerCharacter* playercheck = Cast<APlayerCharacter>(hit.GetActor());
		if (playercheck != NULL && FVector::Distance(Start, player->GetActorLocation()) < shootRange)
		{
			canShoot = true;
		}
		else {
			canShoot = false;
		}
	}
}

void ANPCCharacter::HandleDestruction()
{
	//TODO: Visual/sound effects.
	if (DeathSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
	}

	//Destroy();
}

void ANPCCharacter::FireBullet()
{
	if (canShoot && !cutscene)
	{
		if (Projectile != NULL && ShootingPoint != NULL)
		{
			FVector ProjectileLocation = ShootingPoint->GetComponentLocation();
			FRotator ProjectileRotation = ShootingPoint->GetComponentRotation();

			auto ProjectileRef = GetWorld()->SpawnActor<AProjectile>(Projectile, ProjectileLocation, ProjectileRotation);
			ProjectileRef->SetOwner(this);

		}
	}
	
}

