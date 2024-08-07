// Copyright Epic Games, Inc. All Rights Reserved.

#include "DiaProjectGameMode.h"
#include "DiaProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADiaProjectGameMode::ADiaProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
