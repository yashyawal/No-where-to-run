// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LevelDictionary.generated.h"

/**
 * Contains Map/Level object refferences 
 */

UCLASS()
class NOWHERETORUN_API ULevelDictionary : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly)
	TArray<TSoftObjectPtr<UWorld>> Maps;

};
