// Fill out your copyright notice in the Description page of Project Settings.


#include "CreepSpawnPoint.h"

// Sets default values
ACreepSpawnPoint::ACreepSpawnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACreepSpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACreepSpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

