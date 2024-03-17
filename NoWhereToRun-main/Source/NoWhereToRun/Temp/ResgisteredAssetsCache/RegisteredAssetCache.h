// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RegisteredAssetCache.generated.h"
enum EMapIDS;
class UUserWidget;
/**
 * Object to hold the associated assets of levels , and Utility functions to manage assets 
 */

UCLASS()
class NOWHERETORUN_API URegisteredAssetCache : public UObject
{
	GENERATED_BODY()
public:

	UFUNCTION()
	void PushUIToCache(EMapIDS MapID , UUserWidget* const UserWidget);

	UFUNCTION()
	void RemoveUIAssetsFromViewport(EMapIDS MapID);

private:

	TMap<int32 , TArray<UUserWidget*>> RegisteredUICache;
};
