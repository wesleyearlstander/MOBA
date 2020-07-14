// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MOBAGameMode.generated.h"

UCLASS(minimalapi)
class AMOBAGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMOBAGameMode();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lanes")
	TArray<AActor*> Team1LaneTop;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lanes")
	TArray<AActor*> Team1LaneMiddle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lanes")
	TArray<AActor*> Team1LaneBottom;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lanes")
	TArray<AActor*> Team2LaneTop;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lanes")
	TArray<AActor*> Team2LaneMiddle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lanes")
	TArray<AActor*> Team2LaneBottom;
};



