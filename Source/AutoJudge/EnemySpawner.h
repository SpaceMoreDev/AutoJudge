// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

UCLASS()
class AUTOJUDGE_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void Spawn();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, Category = "Logic Data")
	class APlayerCharacter* player;

	UPROPERTY(EditDefaultsOnly, Category = "Spawn Data")
	TSubclassOf<class ANPCCharacter> enemyToSpawn;
	UPROPERTY(EditDefaultsOnly, Category = "Spawn Data")
	double spawnInterval = 1.0;
	double MaxspawnDistance = 2000.f;
	double MinspawnDistance = 1000.f;
	int maxNPCsInWorld =100;
	bool canSpawn = false;
	FTimerHandle SpawnRateTimerHandle;


};
