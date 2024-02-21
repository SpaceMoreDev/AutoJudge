// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"
#include "PlayerCharacter.h"
#include "NPCCharacter.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	GetWorldTimerManager().SetTimer(SpawnRateTimerHandle, this, &AEnemySpawner::Spawn, spawnInterval, true);
}

void AEnemySpawner::Spawn()
{
	if (canSpawn)
	{

		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ANPCCharacter::StaticClass(), FoundActors);

		if (FoundActors.Num() < maxNPCsInWorld)
		{
			GetWorld()->SpawnActor<ANPCCharacter>(enemyToSpawn, GetActorLocation(), GetActorRotation());
		}
		else {
			if (GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::Printf(TEXT("reached NPC limit")));
		}
	}

}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector playerLocation = player->GetActorLocation();
	FVector directionToplayer = playerLocation - GetActorLocation();;

	if ( FVector::DotProduct(player->GetActorForwardVector(), directionToplayer) > 0.9
		&& FVector::Distance(playerLocation, GetActorLocation()) < MaxspawnDistance
		&& FVector::Distance(playerLocation, GetActorLocation()) > MinspawnDistance)
	{
		canSpawn = true;
	}
	else
	{
		canSpawn = false;
	}

}

