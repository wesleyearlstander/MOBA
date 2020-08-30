// Fill out your copyright notice in the Description page of Project Settings.


#include "CreepWaypoint.h"

FString ACreepWaypoint::ToString()
{
	return FString::Printf(TEXT("%d,%d"), order, Lane);
}
