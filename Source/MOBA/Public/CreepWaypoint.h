// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../MOBA.h"
#include "Engine/TargetPoint.h"
#include "CreepWaypoint.generated.h"

/**
 * 
 */
UCLASS()
class MOBA_API ACreepWaypoint : public ATargetPoint
{
	GENERATED_BODY()


public:

	UPROPERTY(EditAnywhere, blueprintReadWrite, Category = Creep)
	int32 order = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Creep)
	TEnumAsByte<ELane> Lane = ELane::Middle;

	FString ToString();
	
};
