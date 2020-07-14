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
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Creep)
	TEnumAsByte<Lane> lane = Lane::Middle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Creep)
	TEnumAsByte<Team> team = Team::Red;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
