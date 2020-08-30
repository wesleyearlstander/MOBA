// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CreepWaypoint.h"
#include "CreepAIController.generated.h"

/**
 * 
 */
UCLASS()
class MOBA_API ACreepAIController : public AAIController
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, Category = Movement)
	TArray<ACreepWaypoint*> Waypoints;

protected:
	virtual void OnPossess(APawn* InPawn) override;
	
};
