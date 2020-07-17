// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../MOBA.h"
#include "CreepSpawnPoint.generated.h"

UCLASS()
class MOBA_API ACreepSpawnPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACreepSpawnPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup")
	TEnumAsByte<ELane> Lane;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup")
	TEnumAsByte<ETeam> Team;

};
