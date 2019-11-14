// Fill out your copyright notice in the Description page of Project Settings.


#include "S5_TestingGroundsGameMode.h"
#include "InfiniteTerrainGameMode.h"
#include "NavMesh/NavMeshBoundsVolume.h"
#include "EngineUtils.h"

void AInfiniteTerrainGameMode::AddToPoll(ANavMeshBoundsVolume* volumeToAdd)
{
	UE_LOG(LogTemp, Warning, TEXT("NavMesh: %s"), *volumeToAdd->GetName());
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