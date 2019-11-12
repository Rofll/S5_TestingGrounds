// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile.h"
#include "Engine/World.h"

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATile::PlaceActors(TSubclassOf<AActor> toSpawn, int minSpawn, int maxSpawn)
{
	
	FVector min = FVector(0, -2000, 0);
	FVector max = FVector(4000, 2000, 0);

	int numberToSpawn = FMath::RandRange(minSpawn, maxSpawn);

	FBox bounds(min, max);

	for (int32 i = 0; i < numberToSpawn; i++)
	{
		FVector spawnPoint = FMath::RandPointInBox(bounds);
		AActor* spawned = GetWorld()->SpawnActor<AActor>(toSpawn);

	
		spawned->SetActorRelativeLocation(spawnPoint);
		spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	}
}

