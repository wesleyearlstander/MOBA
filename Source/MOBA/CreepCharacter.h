// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MOBA.h"
#include "GameFramework/Character.h"
#include "CreepCharacter.generated.h"

UCLASS()
class MOBA_API ACreepCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACreepCharacter();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Creep)
	TEnumAsByte<ELane> Lane = ELane::Middle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Creep)
	TEnumAsByte<ETeam> Team = ETeam::Red;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Creep)
	int Health = -1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Creep)
	int MaxHealth = -1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Creep)
	int AttackRange = -1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Creep)
	int Damage = -1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Creep)
	float AttackSpeed = -1;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = Creep)
	void TakeDamage(float d);

};
