// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "S5_TestingGroundsGameMode.h"
#include "S5_TestingGroundsHUD.h"
#include "S5_TestingGroundsCharacter.h"
#include "UObject/ConstructorHelpers.h"

AS5_TestingGroundsGameMode::AS5_TestingGroundsGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AS5_TestingGroundsHUD::StaticClass();
}
