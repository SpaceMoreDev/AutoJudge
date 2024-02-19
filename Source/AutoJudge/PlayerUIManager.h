// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerUIManager.generated.h"

class UUserWidget;
class AHUD;
class APlayerController;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AUTOJUDGE_API UPlayerUIManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerUIManager();

	void ChangeToGamePlay();
	void ChangeToPause();
	void ChangeToInspect();
	void ChangeWidget(TSubclassOf<UUserWidget> Widget);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI Settings|Widgets")
	TSubclassOf<UUserWidget>  PauseWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI Settings|Widgets")
	TSubclassOf<UUserWidget>  GameWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI Settings|Widgets")
	TSubclassOf<UUserWidget>  InspectWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI Settings")
	TSubclassOf<AHUD> PlayerHUD;

	UUserWidget* OldWidget = nullptr;

	APlayerController* PlayerControllerRef;
		
};
