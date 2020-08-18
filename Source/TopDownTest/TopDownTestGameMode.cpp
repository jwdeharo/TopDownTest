// Copyright Epic Games, Inc. All Rights Reserved.

#include "TopDownTestGameMode.h"
#include "TopDownTestPlayerController.h"
#include "TopDownTestCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATopDownTestGameMode::ATopDownTestGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ATopDownTestPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}