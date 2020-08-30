// Fill out your copyright notice in the Description page of Project Settings.

#include "CreepCharacter.h"

// Sets default values
ACreepCharacter::ACreepCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACreepCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (GEngine) {
		 if (Health == -1) GEngine->AddOnScreenDebugMessage(INDEX_NONE, 10, FColor::Red, TEXT("Set Creep default health in blueprint"));
		 if (MaxHealth == -1) GEngine->AddOnScreenDebugMessage(INDEX_NONE, 10, FColor::Red, TEXT("Set Creep default max health in blueprint"));
		 if (Damage == -1) GEngine->AddOnScreenDebugMessage(INDEX_NONE, 10, FColor::Red, TEXT("Set Creep default damage in blueprint"));
		 if (AttackRange == -1) GEngine->AddOnScreenDebugMessage(INDEX_NONE, 10, FColor::Red, TEXT("Set Creep default attack range in blueprint"));
		 if (AttackSpeed == -1) GEngine->AddOnScreenDebugMessage(INDEX_NONE, 10, FColor::Red, TEXT("Set Creep default attack speed in blueprint"));
	}
}

// Called every frame
void ACreepCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACreepCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

