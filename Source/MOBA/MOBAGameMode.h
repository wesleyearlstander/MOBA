// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Public/CreepWaypoint.h"
#include "Public/CreepSpawnPoint.h"
#include "CreepCharacter.h"
#include "MOBAGameMode.generated.h"

UCLASS(minimalapi)
class AMOBAGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMOBAGameMode();

	//Blueprint References
	UPROPERTY(EditAnywhere, Category = "Creeps")
	TSubclassOf<ACreepWaypoint> CreepWaypointBlueprint;

	UPROPERTY(EditAnywhere, Category = "Creeps")
	TSubclassOf<ACreepSpawnPoint> CreepSpawnPointBlueprint;

	UPROPERTY(EditAnywhere, Category = "Creeps")
	TSubclassOf<ACreepCharacter> CreepBlueprint;

	//Creep Lane setup
	UPROPERTY(EditAnywhere, Category = "Lanes")
	AActor* WaypointHolder;
	
	UPROPERTY(BlueprintReadWrite, Category = "Lanes")
	TArray<ACreepWaypoint*> Team1LaneTop;

	UPROPERTY(BlueprintReadWrite, Category = "Lanes")
	TArray<ACreepWaypoint*> Team1LaneMiddle;

	UPROPERTY(BlueprintReadWrite, Category = "Lanes")
	TArray<ACreepWaypoint*> Team1LaneBottom;

	UPROPERTY(BlueprintReadWrite, Category = "Lanes")
	TArray<ACreepWaypoint*> Team2LaneTop;

	UPROPERTY(BlueprintReadWrite, Category = "Lanes")
	TArray<ACreepWaypoint*> Team2LaneMiddle;

	UPROPERTY(BlueprintReadWrite, Category = "Lanes")
	TArray<ACreepWaypoint*> Team2LaneBottom;

	UPROPERTY(BlueprintReadWrite, Category = "Creeps")
	TArray<ACreepSpawnPoint*> CreepSpawnPoints;

	UPROPERTY(BlueprintReadWrite, Category = "Lanes")
	TArray<int32> WaypointCounts;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Lanes")
	float WaveRespawnTime;

protected:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void StartPlay() override;
	virtual void GatherCreepWaypoints();

private:
	FTimerHandle WaveRespawnTimer;
	FTimerHandle CreepSpawnTimer;

	TArray<ACreepCharacter*> Creeps;

	//Spawns Creep Wave
	void SpawnCreepWave(uint8 num);

	void SpawnCreep(uint8 spawnIndex);//TODO: can set type later

public:
	void GetWaypoints(ACreepCharacter* Creep);
};



