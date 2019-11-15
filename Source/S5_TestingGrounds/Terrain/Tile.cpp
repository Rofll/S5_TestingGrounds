// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "ActorPool.h"
#include "NavigationSystem.h"

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	navigationBoundsOffset = FVector(2000, 0, 0);

	minExtent = FVector(0, -2000, 0);
	maxExtent = FVector(4000, 2000, 0);
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();

}

void ATile::EndPlay(const EEndPlayReason::Type endPlayReason)
{
	pool->Return(navMeshBoundsVolume);
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATile::SetPool(UActorPool* inPool)
{
	UE_LOG(LogTemp, Warning, TEXT("[%s] SettingPool %s"), *(this->GetName()), *(inPool->GetName()));

	pool = inPool;

	PositionNavMeshBoundsVolume();
}

void ATile::PositionNavMeshBoundsVolume()
{
	navMeshBoundsVolume = pool->Checkout();

	if (navMeshBoundsVolume == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[%s] Not enoghu actors in pool."), *GetName());
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("[%s]Checked out: {%s}"), *GetName(), *navMeshBoundsVolume->GetName());

	navMeshBoundsVolume->SetActorLocation(GetActorLocation() + navigationBoundsOffset);

	FNavigationSystem::Build(*GetWorld());
	
}

void ATile::PlaceActors(TSubclassOf<AActor> toSpawn, int minSpawn, int maxSpawn, float radius, float minScale, float maxScale)
{
	TArray<FSpawnPosition> spawnPositions = RandomSpawnPositions(minSpawn, maxSpawn, radius, minScale, maxScale);

	for (FSpawnPosition spawnPosition : spawnPositions)
	{
		PlaceActor(toSpawn, spawnPosition);
	}
}

bool ATile::CanSpawnAtLocation(FVector location, float radius)
{
	FHitResult hitResult;

	FVector globalLocation = ActorToWorld().TransformPosition(location);

	bool hasHit = GetWorld()->SweepSingleByChannel(hitResult, globalLocation, globalLocation + FVector(0,0,.001f), FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2, FCollisionShape::MakeSphere(radius));

	return !hasHit;
}

TArray<FSpawnPosition> ATile::RandomSpawnPositions(int minSpawn, int maxSpawn, float radius, float minScale, float maxScale)
{
	TArray<FSpawnPosition> spawnPositions;

	int numberToSpawn = FMath::RandRange(minSpawn, maxSpawn);

	for (int32 i = 0; i < numberToSpawn; i++)
	{
		FVector spawnPoint;

		float randomScale = FMath::RandRange(minScale, maxScale);

		bool found = FindEmptyLocation(spawnPoint, radius * randomScale);

		if (found)
		{
			float randomRotation = FMath::RandRange(-180.f, 180.f);

			spawnPositions.Add(FSpawnPosition(spawnPoint, radius, randomScale));
		}
	}

	return spawnPositions;
}

bool ATile::FindEmptyLocation(FVector& outLocation, float radius)
{
	FBox bounds(minExtent, maxExtent);

	const int MAX_ATTEMPS = 100;

	for (int i = 0; i < MAX_ATTEMPS; i++)
	{
		FVector candidatePoint = FMath::RandPointInBox(bounds);

		if (CanSpawnAtLocation(candidatePoint, radius))
		{
			outLocation = candidatePoint;
			return true;
		}
	}

	return false;
}

void ATile::PlaceActor(TSubclassOf<AActor> toSpawn, FSpawnPosition spawnPosition)
{
	AActor* spawned = GetWorld()->SpawnActor<AActor>(toSpawn);
	spawned->SetActorRelativeLocation(spawnPosition.location);
	spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	spawned->SetActorRotation(FRotator(0, spawnPosition.rotation, 0));
	spawned->SetActorScale3D(FVector(spawnPosition.scale, spawnPosition.scale, spawnPosition.scale));
}

