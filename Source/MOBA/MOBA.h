// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(LogMOBA, Log, All);

UENUM(BlueprintType)
enum Lane
{
	Top		UMETA(DisplayName = "Top"),
	Middle	UMETA(DisplayName = "Middle"),
	Bottom	UMETA(DisplayName = "Bottom")
};

UENUM(BlueprintType)
enum Team
{
	Red		UMETA(DisplayName = "Red"),
	Blue	UMETA(DisplayName = "Blue")
};
