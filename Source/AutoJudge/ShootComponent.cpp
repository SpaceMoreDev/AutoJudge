// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootComponent.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UShootComponent::UShootComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UShootComponent::BeginPlay()
{
	Super::BeginPlay();

	player = UGameplayStatics::GetPlayerPawn(this, 0);
	
}


// Called every frame
void UShootComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UShootComponent::Fire()
{
	FVector ProjectileLocation = SpawnPoint->GetComponentLocation();
	FRotator ProjectileRotation = SpawnPoint->GetComponentRotation();

	auto ProjectileRef = GetWorld()->SpawnActor<AProjectile>(Projectile, ProjectileLocation, ProjectileRotation);
	ProjectileRef->SetOwner(player);
}