// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "S5_TestingGroundsGameMode.h"
#include "InfiniteTerrainGameMode.generated.h"

/**
 * 
 */
UCLASS()
class S5_TESTINGGROUNDS_API AInfiniteTerrainGameMode : public AS5_TestingGroundsGameMode
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Bounds Pool")
	void PopulateBoundsVolumePool();

private:
	void AddToPoll(class ANavMeshBoundsVolume* volumeToAdd);
};
