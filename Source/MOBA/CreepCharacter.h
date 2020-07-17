// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MOBA.h"
#include "GameFramework/Character.h"
#include "Public/CreepWaypoint.h"
#include "CreepCharacter.generated.h"

UCLASS()
class MOBA_API ACreepCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACreepCharacter();

	UPROPERTY(BlueprintReadWrite, Category = Movement)
	TArray<ACreepWaypoint*> Waypoints;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Creep)
	TEnumAsByte<ELane> Lane = ELane::Middle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Creep)
	TEnumAsByte<ETeam> Team = ETeam::Red;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
