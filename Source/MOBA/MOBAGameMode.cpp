// Copyright Epic Games, Inc. All Rights Reserved.

#include "MOBAGameMode.h"
#include "MOBAPlayerController.h"
#include "MOBACharacter.h"
#include "kismet/GameplayStatics.h"
#include "Public/CreepAIController.h"
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

	SpawnCreepWave(1);
}

void AMOBAGameMode::StartPlay() {
	Super::StartPlay();
	//SpawnCreepWave(5);
}

void AMOBAGameMode::GatherCreepWaypoints()
{
	TArray<AActor*> Waypoints;
	TArray<AActor*> Points;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), CreepWaypointBlueprint, Waypoints); //TODO: optimize with folder and reference
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), CreepSpawnPointBlueprint, Points);

	uint8 num = Points.Num();
	CreepSpawnPoints.Init(nullptr, num);
	for (uint8 i = 0; i < num; ++i) {
		CreepSpawnPoints[i] = Cast<ACreepSpawnPoint>(Points[i]);
	}

	uint16 count = Waypoints.Num();

	//TODO: Can parallize this for large amount of waypoints 
	for (uint16 i = 0; i < count; ++i) { //Count waypoints for each lane
		ACreepWaypoint* waypoint = Cast<ACreepWaypoint>(Waypoints[i]);
		WaypointCounts[(int)(waypoint->Lane)]++;
	}
	Team1LaneTop.Init(nullptr, WaypointCounts[(int)(ELane::Top)]);
	Team2LaneTop.Init(nullptr, WaypointCounts[(int)(ELane::Top)]);
	Team1LaneMiddle.Init(nullptr, WaypointCounts[(int)(ELane::Middle)]);
	Team2LaneMiddle.Init(nullptr, WaypointCounts[(int)(ELane::Middle)]);
	Team1LaneBottom.Init(nullptr, WaypointCounts[(int)(ELane::Bottom)]);
	Team2LaneBottom.Init(nullptr, WaypointCounts[(int)(ELane::Bottom)]);
	//UE_LOG(LogTemp, Warning, TEXT("%d,%d,%d"), WaypointCounts[(int)(ELane::Top)], WaypointCounts[(int)(ELane::Middle)], WaypointCounts[(int)(ELane::Bottom)]);

	for (uint16 i = 0; i < count; ++i) {
		ACreepWaypoint* waypoint = Cast<ACreepWaypoint>(Waypoints[i]);
		switch (waypoint->Lane) {
		case ELane::Top: {
			Team1LaneTop[waypoint->order] = waypoint;
			Team2LaneTop[WaypointCounts[(int)(ELane::Top)] - 1 - waypoint->order] = waypoint;
			break;
		}
		case ELane::Middle: {
			Team1LaneMiddle[waypoint->order] = waypoint;
			Team2LaneMiddle[WaypointCounts[(int)(ELane::Middle)] - 1 - waypoint->order] = waypoint;
			break;
		}
		case ELane::Bottom: {
			Team1LaneBottom[waypoint->order] = waypoint;
			Team2LaneBottom[WaypointCounts[(int)(ELane::Bottom)] - 1 - waypoint->order] = waypoint;
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
	ACreepCharacter* Creep = GetWorld()->SpawnActorDeferred<ACreepCharacter>(CreepBlueprint, CreepSpawnPoints[spawnIndex]->GetActorTransform());
	Creep->Lane = CreepSpawnPoints[spawnIndex]->Lane;
	Creep->Team = CreepSpawnPoints[spawnIndex]->Team;
	UGameplayStatics::FinishSpawningActor(Creep, CreepSpawnPoints[spawnIndex]->GetActorTransform());
	Creeps.Add(Creep);
}

void AMOBAGameMode::GetWaypoints(ACreepCharacter* Creep)
{
	ACreepAIController* CreepAI = Cast<ACreepAIController>(Creep->GetController());
	switch (Creep->Lane) {
	case ELane::Top: if (Creep->Team == ETeam::Blue) CreepAI->Waypoints.Append(Team1LaneTop); else CreepAI->Waypoints.Append(Team2LaneTop); break;
	case ELane::Middle: if (Creep->Team == ETeam::Blue) CreepAI->Waypoints.Append(Team1LaneMiddle); else CreepAI->Waypoints.Append(Team2LaneMiddle); break;
	case ELane::Bottom: if (Creep->Team == ETeam::Blue) CreepAI->Waypoints.Append(Team1LaneBottom); else CreepAI->Waypoints.Append(Team2LaneBottom); break;
	default: checkNoEntry(); break;
	}
}
