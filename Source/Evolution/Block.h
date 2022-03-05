// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Block.generated.h"

UCLASS()
class EVOLUTION_API ABlock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlock();

	//Verify is it is Bomb or clean
	void Verification();

	//Verify is it is Bomb or clean
	void ChadVerification();

	//Mark
	void Mark();

	//Clicked: "Destroy", Warn About Bomb
	void ChangePosition();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game") bool mine;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game") int nearMine = 1;
	UPROPERTY(EditAnywhere, Category = "Game") int xPos;
	UPROPERTY(EditAnywhere, Category = "Game") int yPos;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game") AActor* SelfReference;

	UPROPERTY(BlueprintReadOnly) bool showed = false;
	UPROPERTY(BlueprintReadOnly) bool marked = false;
	TArray<AActor*> FoundBlocks;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
