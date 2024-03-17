// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include <NoWhereToRun/UI/EntryMenu.h>
#include <NoWhereToRun/UI/OptionMenu.h>
#include <NowhereToRun/Enumerations/MapIDS.h>
#include "UIDictionary.generated.h"
/**
 * Stores refferences for UI assets
 */
UCLASS()
class NOWHERETORUN_API UUIDictionary : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UEntryMenu> EntryMenuUIAsset;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UOptionMenu> OptionMenuUIAsset;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> CrossHairUIAsset;

};