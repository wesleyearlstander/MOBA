// Copyright Epic Games, Inc. All Rights Reserved.

#include "MOBAGameMode.h"
#include "MOBAPlayerController.h"
#include "MOBACharacter.h"
#include "UObject/ConstructorHelpers.h"

AMOBAGameMode::AMOBAGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AMOBAPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}