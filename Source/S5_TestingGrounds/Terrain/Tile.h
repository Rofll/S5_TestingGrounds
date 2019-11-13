// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

UCLASS()
class S5_TESTINGGROUNDS_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

	UFUNCTION(BlueprintCallable, Category = "Tile")
	void PlaceActors(TSubclassOf<AActor> toSpawn, int minSpawn = 1, int maxSpawn = 1, float radius = 500, float minScale = 1, float maxScale = 1);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	
	bool FindEmptyLocation(FVector& outLocation ,float radius);
	void PlaceActor(TSubclassOf<AActor> toSpawn, FVector spawnPoint, float rotation, float scale);
	bool CanSpawnAtLocation(FVector location, float radius);

};
