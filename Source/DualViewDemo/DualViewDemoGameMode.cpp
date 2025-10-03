// Copyright Epic Games, Inc. All Rights Reserved.

#include "DualViewDemoGameMode.h"
#include "DualViewDemoCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADualViewDemoGameMode::ADualViewDemoGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
