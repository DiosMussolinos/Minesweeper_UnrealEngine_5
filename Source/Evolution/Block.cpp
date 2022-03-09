// Fill out your copyright notice in the Description page of Project Settings.


#include "Block.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABlock::ABlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABlock::BeginPlay()
{
	Super::BeginPlay();

	MineRandomization();
}

void ABlock::MineRandomization()
{
	#pragma region Randomize if a cube is also a mine - 30% for now
	int random = FMath::RandRange(0, 10);

	if (random < 3)
	{
		mine = true;
	}

	SelfReference = this;
	#pragma endregion
}

void ABlock::CalculateMines(TArray<AActor*> Blocks)
{
	#pragma region Calculate All Mines Around Cubes

	TotalBlocks = Blocks;

	for (int i = 0; i < TotalBlocks.Num(); i++)
	{
		ABlock* blockCast = Cast<ABlock>(TotalBlocks[i]);

		if (blockCast->SelfReference != SelfReference)
		{
			int xDif = xPos - blockCast->xPos;
			int yDif = yPos - blockCast->yPos;

			if (xDif == 1 || xDif == -1 || xDif == 0)
			{
				if (yDif == 1 || yDif == -1 || yDif == 0)
				{
					if (blockCast->mine && !mine)
					{
						nearMine++;
					}
				}
			}
		}
	}

	#pragma endregion
}

void ABlock::Verification()
{
	for (int i = 0; i < TotalBlocks.Num(); i++)
	{
		ABlock* blockCast = Cast<ABlock>(TotalBlocks[i]);
 
		int xDif = xPos - blockCast->xPos;
		int yDif = yPos - blockCast->yPos;

		if (!blockCast->showed)
		{
			if (xDif == 1 || xDif == -1 || xDif == 0)
			{
				if (yDif == 1 || yDif == -1 || yDif == 0)
				{
					if (!blockCast->mine)
					{
						if (!blockCast->marked)
						{
							blockCast->ChangePosition();
							blockCast->ChadVerification();
							blockCast->showed = true;
						}
					}
				}
			}
		}
	}
}

void ABlock::ChangePosition()
{
	FVector newPos = FVector(GetActorLocation().X, GetActorLocation().Y, -100);
	SetActorLocation(newPos);
}

//ChadVerification is to make Verification NOT StackOverflow
void ABlock::ChadVerification()
{
	for (int i = 0; i < TotalBlocks.Num(); i++)
	{
		ABlock* blockCast = Cast<ABlock>(TotalBlocks[i]);

		int xDif = xPos - blockCast->xPos;
		int yDif = yPos - blockCast->yPos;

		if (!blockCast->showed)
		{
			if (xDif == 1 || xDif == -1 || xDif == 0)
			{
				if (yDif == 1 || yDif == -1 || yDif == 0)
				{
					if (!blockCast->mine)
					{
						if (!blockCast->marked)
						{
							blockCast->ChangePosition();
							blockCast->showed = true;
						}
					}
				}
			}
		}
	}
}