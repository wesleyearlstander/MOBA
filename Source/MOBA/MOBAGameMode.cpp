// Copyright Epic Games, Inc. All Rights Reserved.

#include "MOBAGameMode.h"
#include "MOBAPlayerController.h"
#include "MOBACharacter.h"
#include "kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

AMOBAGameMode::AMOBAGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AMOBAPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AMOBAGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) {
	Super::InitGame(MapName,Options,ErrorMessage);
	WaypointCounts.Init(0, 3);

	//verify(WaypointHolder != nullptr);

	if (GEngine) { //check blueprints are set
		if (CreepBlueprint == nullptr) GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5, FColor::Red, TEXT("Creep blueprint not set"));
		if (CreepWaypointBlueprint == nullptr) GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5, FColor::Red, TEXT("Creep waypoint blueprint not set"));
		if (CreepSpawnPointBlueprint == nullptr) GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5, FColor::Red, TEXT("Creep spawn point blueprint not set"));
	}
	//GetWorld()->GetTimerManager().SetTimer()

	GatherCreepWaypoints();
	//SpawnCreepWave(5);
}

void AMOBAGameMode::StartPlay() {
	Super::StartPlay();
	SpawnCreepWave(5);
}

void AMOBAGameMode::GatherCreepWaypoints()
{
	TArray<AActor*> Waypoints;
	TArray<AActor*> Points;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), CreepWaypointBlueprint, Waypoints); //TODO: optimize with folder and reference
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), CreepSpawnPointBlueprint, Points);

	uint8 num = Points.Num();
	CreepSpawnPoints.Init(NULL, num);
	for (uint8 i = 0; i < num; ++i) {
		CreepSpawnPoints[i] = Cast<ACreepSpawnPoint>(Points[i]);
	}

	uint16 count = Waypoints.Num();

	//TODO: Can parallize this for large amount of waypoints 
	for (uint16 i = 0; i < count; ++i) { //Count waypoints for each lane
		ACreepWaypoint* waypoint = Cast<ACreepWaypoint>(Waypoints[i]);
		WaypointCounts[(int8)(waypoint->Lane)]++;
	}

	Team1LaneTop.Init(NULL, WaypointCounts[(int8)(ELane::Top)]);
	Team2LaneTop.Init(NULL, WaypointCounts[(int8)(ELane::Top)]);
	Team1LaneMiddle.Init(NULL, WaypointCounts[(int8)(ELane::Middle)]);
	Team2LaneMiddle.Init(NULL, WaypointCounts[(int8)(ELane::Middle)]);
	Team1LaneBottom.Init(NULL, WaypointCounts[(int8)(ELane::Bottom)]);
	Team2LaneBottom.Init(NULL, WaypointCounts[(int8)(ELane::Bottom)]);

	for (uint16 i = 0; i < count; ++i) {
		ACreepWaypoint* waypoint = Cast<ACreepWaypoint>(Waypoints[i]);
		switch (waypoint->Lane) {
		case ELane::Top: {
			Team1LaneTop.Insert(waypoint, waypoint->order);
			Team2LaneTop.Insert(waypoint, WaypointCounts[(int8)(ELane::Top)] - 1 - waypoint->order);
			break;
		}
		case ELane::Middle: {
			Team1LaneMiddle.Insert(waypoint, waypoint->order);
			Team2LaneMiddle.Insert(waypoint, WaypointCounts[(int8)(ELane::Middle)] - 1 - waypoint->order);
			break;
		}
		case ELane::Bottom: {
			Team1LaneBottom.Insert(waypoint, waypoint->order);
			Team2LaneBottom.Insert(waypoint, WaypointCounts[(int8)(ELane::Bottom)] - 1 - waypoint->order);
			break;
		}
		default: checkNoEntry(); //Crash if more lanes
		}
	}
}

void AMOBAGameMode::SpawnCreepWave(uint8 num) {
	uint8 spawnCount = CreepSpawnPoints.Num();
	for (uint8 i = 0; i < num; ++i) {
		for (uint8 j = 0; j < spawnCount; ++j) {
			SpawnCreep(j);
		}
	}
}

void AMOBAGameMode::SpawnCreep(uint8 spawnIndex)
{
	Creeps.Add(GetWorld()->SpawnActorDeferred<ACreepCharacter>(CreepBlueprint, CreepSpawnPoints[spawnIndex]->GetActorTransform()));
	Creeps.Last()->Lane = CreepSpawnPoints[spawnIndex]->Lane;
	Creeps.Last()->Team = CreepSpawnPoints[spawnIndex]->Team;
	GetWaypoints(Creeps.Last());
	UGameplayStatics::FinishSpawningActor(Creeps.Last(), CreepSpawnPoints[spawnIndex]->GetActorTransform());
}

void AMOBAGameMode::GetWaypoints(ACreepCharacter* Creep)
{
	switch (Creep->Lane) {
	case ELane::Top: (Creep->Team == ETeam::Blue) ? Creep->Waypoints = Team1LaneTop : Creep->Waypoints = Team2LaneTop; break;
	case ELane::Middle: (Creep->Team == ETeam::Blue) ? Creep->Waypoints = Team1LaneMiddle : Creep->Waypoints = Team2LaneMiddle; break;
	case ELane::Bottom: (Creep->Team == ETeam::Blue) ? Creep->Waypoints = Team1LaneBottom : Creep->Waypoints = Team2LaneBottom; break;
	default: checkNoEntry(); break;
	}
}
