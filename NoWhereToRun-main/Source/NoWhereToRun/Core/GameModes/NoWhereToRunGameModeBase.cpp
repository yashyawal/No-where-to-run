// Copyright Epic Games, Inc. All Rights Reserved.


#include "NoWhereToRunGameModeBase.h"
#include <NoWhereToRun/Core/GameInstance/GlobalGameInstance.h>
#include <NoWhereToRun/Data/LevelDictionary.h>
#include <NoWhereToRun/Enumerations/MapIDS.h>
#include <NowhereToRun/Level/LevelManager.h>

void ANoWhereToRunGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	if (auto Gameinstance = Cast<UGlobalGameInstance>(GetWorld()->GetGameInstance()))
	{
		if (const auto LevelManager = Gameinstance->GetLevelManager())
		{
			LevelManager->LoadLevel(EMapIDS::E_EntryStage);
		}
	}
}
