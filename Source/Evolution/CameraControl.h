// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CameraControl.generated.h"

/**
 * 
 */
UCLASS()
class EVOLUTION_API ACameraControl : public APlayerController
{
	GENERATED_BODY()
	
public:
	ACameraControl();

	// 0 = normal, 1 = win, 2 = lose
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game") int state = 0;

protected:

	// Called in the First Frame.
	virtual void BeginPlay() override;

	//Create Blocks
	void CreateBlocks();

	//Call To calculate all Mines
	void CallBlockMineVer();

	//Inputs
	virtual void SetupInputComponent() override;

	//Left Click
	void LeftClick();
	
	//Right Click
	void RightClick();

	//Help
	void Help();

	//Show Map
	void Map();

private:
	UPROPERTY(EditAnywhere, Category = "Game") TSubclassOf<AActor> cameraActor;
	UPROPERTY(EditAnywhere, Category = "Game") int xLenght;
	UPROPERTY(EditAnywhere, Category = "Game") int yHeight;
	UPROPERTY(EditAnywhere, Category = "Game") TSubclassOf<AActor> block_;
	UPROPERTY(EditAnywhere, Category = "Game") FVector initialPos;


};