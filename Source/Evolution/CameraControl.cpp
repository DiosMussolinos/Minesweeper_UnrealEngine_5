// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraControl.h"
#include "Block.h"
#include "WebSocketInstance.h"

ACameraControl::ACameraControl()
{
	bShowMouseCursor = true;
}

void ACameraControl::BeginPlay()
{
	#pragma region Create Blocks
	for (int x = 0; x < xLenght; x++)
	{
		for (int y = 0; y < yHeight; y++)
		{
			FVector newPos = FVector(initialPos.X + (100 * x), initialPos.Y + (100 * y), 0);

			ABlock* SpawnedBlock = GetWorld()->SpawnActor<ABlock>(block_, newPos, FRotator(0, 0, 0));

			SpawnedBlock->xPos = x;
			SpawnedBlock->yPos = y;
		}
	}
	#pragma endregion
}

//Inputs
void ACameraControl::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("LeftClick", IE_Released, this, &ACameraControl::LeftClick);

	InputComponent->BindAction("RightClick", IE_Pressed, this, &ACameraControl::RightClick);

	InputComponent->BindAction("Map", IE_Pressed, this, &ACameraControl::Map);

	InputComponent->BindAction("Help", IE_Pressed, this, &ACameraControl::Help);

}

void ACameraControl::LeftClick()
{
	//Raycast From camera to mouse Pos in world
	//if - Pointer Not Null
	//if - actor.Tag Block
	//Block->Verify()
	
	if (cameraActor)
	{
		if (state == 0)
		{
			FHitResult Hit;
			GetHitResultUnderCursor(ECC_Visibility, false, Hit);

			AActor* ActorHit = Hit.GetActor();

			if (ActorHit)
			{
				if (ActorHit->ActorHasTag(TEXT("Block")))
				{
					ABlock* block = Cast<ABlock>(ActorHit);

					if (block->mine)
					{
						state = 2;
						block->showed = true;
					}
					else
					{
						if ((!block->showed) && (!block->marked))
						{
							//Local Change
							block->ChangePosition();
							block->Verification();
							block->showed = true;

							//WebSocket
							UWebSocketInstance* GameInst = Cast<UWebSocketInstance>(GetGameInstance());
							
							if (GameInst)
							{
								if (GameInst->webSocket->IsConnected())
								{
									FString message = "Open <"+ FString::FromInt(block->xPos) +"> <"+ FString::FromInt(block->yPos) +">";
									GameInst->webSocket->Send(message);
								}
							}
						}
					}
				}
			}
		}
	}
}

void ACameraControl::RightClick()
{
	//Raycast To Cube
	//Spawn flag at the center of the cube

	if (cameraActor)
	{
		if (state == 0)
		{
			FHitResult Hit;
			GetHitResultUnderCursor(ECC_Visibility, false, Hit);

			AActor* ActorHit = Hit.GetActor();

			if (ActorHit)
			{
				if (ActorHit->ActorHasTag(TEXT("Block")))
				{
					ABlock* block = Cast<ABlock>(ActorHit);

					block->marked = true;
				}
			}
		}
	}

}

void ACameraControl::Map()
{
	//Request Map Websocket
	UWebSocketInstance* GameInst = Cast<UWebSocketInstance>(GetGameInstance());

	if (GameInst)
	{
		if (GameInst->webSocket->IsConnected())
		{
			FString message = "map";
			GameInst->webSocket->Send(message);
		}
	}

}

void ACameraControl::Help()
{
	//Request Help WebSocket
	UWebSocketInstance* GameInst = Cast<UWebSocketInstance>(GetGameInstance());

	if (GameInst)
	{
		if (GameInst->webSocket->IsConnected())
		{
			FString message = "help";
			GameInst->webSocket->Send(message);
		}
	}
}

