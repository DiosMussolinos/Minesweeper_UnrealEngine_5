// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "evoTest.generated.h"

/**
 * 
 */
UCLASS()
class EVOLUTION_API UevoTest : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()


		UFUNCTION(BlueprintCallable)
		static TArray<int> EvoTestValue(TArray<int> notes, int value);
	
};
