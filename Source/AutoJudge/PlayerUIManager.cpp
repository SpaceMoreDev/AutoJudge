// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerUIManager.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UPlayerUIManager::UPlayerUIManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UPlayerUIManager::ChangeToGamePlay()
{
	if (IsValid(GameWidget))
		ChangeWidget(GameWidget);
}

void UPlayerUIManager::ChangeToPause()
{
	if (IsValid(PauseWidget))
		ChangeWidget(PauseWidget);
}

void UPlayerUIManager::ChangeToInspect()
{
	if (IsValid(InspectWidget))
		ChangeWidget(InspectWidget);
}

void UPlayerUIManager::ChangeWidget(TSubclassOf<UUserWidget> newWidget)
{
	if (OldWidget)
		delete OldWidget;

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 12.0f, FColor::Blue, FString::Printf(TEXT("UI Changed to %s"), *newWidget->GetName()));

	OldWidget = CreateWidget<UUserWidget>(PlayerControllerRef, newWidget);
	OldWidget->AddToViewport();
}


// Called when the game starts
void UPlayerUIManager::BeginPlay()
{
	Super::BeginPlay();

	PlayerControllerRef = UGameplayStatics::GetPlayerController(GetOwner(), 0);
	ChangeToGamePlay();
	
}


// Called every frame
void UPlayerUIManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

