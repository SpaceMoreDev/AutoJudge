// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "AIController.h"

// Sets default values
ANPCCharacter::ANPCCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	npcMesh = Super::GetMesh();

}

// Called when the game starts or when spawned
void ANPCCharacter::BeginPlay()
{
	Super::BeginPlay();
	playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	
}

// Called every frame
void ANPCCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (playerController != NULL)
	{
		FVector locationToPlayer = playerController->GetPawn()->GetActorLocation();
		FVector dirToPlayer = locationToPlayer - GetActorLocation();
		dirToPlayer.Z = 0.f;

		AddMovementInput(dirToPlayer, MoveSpeed*GetWorld()->DeltaTimeSeconds);
	}
}

