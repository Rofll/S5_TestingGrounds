// Fill out your copyright notice in the Description page of Project Settings.


#include "S5_TestingGroundsGameMode.h"
#include "InfiniteTerrainGameMode.h"
#include "NavMesh/NavMeshBoundsVolume.h"
#include "EngineUtils.h"
#include "ActorPool.h"

AInfiniteTerrainGameMode::AInfiniteTerrainGameMode()
{
	navMeshBoundsVolumePool = CreateDefaultSubobject<UActorPool>(FName("Nav Mesh Bounds Volume Pool"));
}

void AInfiniteTerrainGameMode::PopulateBoundsVolumePool()
{
	TActorIterator<ANavMeshBoundsVolume> volumeIterator = TActorIterator<ANavMeshBoundsVolume>(GetWorld());

	while (volumeIterator)
	{
		AddToPoll(*volumeIterator);
		++volumeIterator;
	}
}

void AInfiniteTerrainGameMode::AddToPoll(ANavMeshBoundsVolume* volumeToAdd)
{
	navMeshBoundsVolumePool->Add(volumeToAdd);
}