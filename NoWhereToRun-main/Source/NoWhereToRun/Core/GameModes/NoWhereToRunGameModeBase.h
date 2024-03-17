// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NoWhereToRunGameModeBase.generated.h"

/**
 * Handles Level related functionalities
 */
UCLASS()
class NOWHERETORUN_API ANoWhereToRunGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
private:
	void BeginPlay() override;
};
