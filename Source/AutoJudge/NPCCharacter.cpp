// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCCharacter.h"
#include "PlayerCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "AIController.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ANPCCharacter::ANPCCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	npcMesh = Super::GetMesh();
	Super::GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;

}

// Called when the game starts or when spawned
void ANPCCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	//SpawnDefaultController();
	player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	
}

// Called every frame
void ANPCCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (player != NULL)
	{
		FVector locationToPlayer = player->GetActorLocation();
		FVector dirToPlayer = locationToPlayer - GetActorLocation();
		dirToPlayer.Z = 0.f;
		DrawDebugLine(GetWorld(), GetActorLocation(), locationToPlayer, FColor::Red, false, .2f);

		AddMovementInput(dirToPlayer, MoveSpeed);
		
	}
}

