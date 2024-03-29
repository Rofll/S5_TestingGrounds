// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"


USTRUCT()
struct FSpawnPosition
{
	GENERATED_USTRUCT_BODY()

	FSpawnPosition(const FVector location, const float rotation, const float scale)
	{
		this->location = location;
		this->rotation = rotation;
		this->scale = scale;
	}

	FSpawnPosition()
	{
		location = FVector::ZeroVector;
		rotation = 0;
		scale = 0;
	}

	FVector location;
	float rotation;
	float scale;
};


class UActorPool;

UCLASS()
class S5_TESTINGGROUNDS_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void PlaceActors(TSubclassOf<AActor> toSpawn, int minSpawn = 1, int maxSpawn = 1, float radius = 500, float minScale = 1, float maxScale = 1);

	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void PlaceAIPawns(TSubclassOf<APawn> toSpawn, int minSpawn = 1, int maxSpawn = 1, float radius = 500);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type endPlayReason) override;

	UPROPERTY(EditDefaultsOnly, Category = "Navigation")
	FVector navigationBoundsOffset;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	FVector minExtent;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	FVector maxExtent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UFUNCTION(BlueprintCallable, Category = "Pool")
	void SetPool(UActorPool* inPool);

	


private:
	
	bool FindEmptyLocation(FVector& outLocation ,float radius);
	template<class T>
	void RandomlyPlaceActors(TSubclassOf<T> toSpawn, int minSpawn, int maxSpawn, float radius, float minScale, float maxScale);
	void PlaceActor(TSubclassOf<AActor> toSpawn, FSpawnPosition spawnPosition);
	void PlaceActor(TSubclassOf<APawn> toSpawn, FSpawnPosition spawnPosition);
	bool CanSpawnAtLocation(FVector location, float radius);
	UActorPool* pool;
	void PositionNavMeshBoundsVolume();
	AActor* navMeshBoundsVolume;

};
