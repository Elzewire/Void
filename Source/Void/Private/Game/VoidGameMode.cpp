// Copyright Epic Games, Inc. All Rights Reserved.

#include "Game/VoidGameMode.h"
#include "Player/VoidCharacter.h"
#include "UObject/ConstructorHelpers.h"

AVoidGameMode::AVoidGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
