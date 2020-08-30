// Fill out your copyright notice in the Description page of Project Settings.

#include "../MOBAGameMode.h"
#include "CreepAIController.h"

void ACreepAIController::OnPossess(APawn* InPawn) {
	Super::OnPossess(InPawn);
	ACreepCharacter* Creep = Cast<ACreepCharacter>(InPawn);
	//UE_LOG(LogTemp, Warning, TEXT("Creep:%d,%d"), (int)Creep->Lane, (int)Creep->Team);
	AMOBAGameMode* mode = GetWorld()->GetAuthGameMode<AMOBAGameMode>();
	if (mode != nullptr) {
		mode->GetWaypoints(Creep);
		//UE_LOG(LogTemp, Warning, TEXT("Waypoints:%d,%d"), (int)Waypoints[0]->Lane, (int)Waypoints[0]->order);
	}
}

