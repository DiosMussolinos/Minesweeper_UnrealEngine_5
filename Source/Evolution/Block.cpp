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

	int random = FMath::RandRange(0, 10);
	
	if (random < 4)
	{
		mine = true;
	}

	SelfReference = this;
}

// Called every frame
void ABlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABlock::ChangePosition()
{
	FVector newPos = FVector(GetActorLocation().X, GetActorLocation().Y, -100);
	SetActorLocation(newPos);
}

void ABlock::Verification()
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABlock::StaticClass(), FoundBlocks);

	for (int i = 0; i < FoundBlocks.Num(); i++)
	{
		ABlock* blockCast = Cast<ABlock>(FoundBlocks[i]);
 
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
					else
					{
						nearMine++;
					}
				}
			}
		}
	}
}


//ChadVerification is to make Verification NOT StackOverflow
void ABlock::ChadVerification()
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABlock::StaticClass(), FoundBlocks);

	for (int i = 0; i < FoundBlocks.Num(); i++)
	{
		ABlock* blockCast = Cast<ABlock>(FoundBlocks[i]);

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
					else
					{
						nearMine++;
					}
				}
			}
		}
	}
}
