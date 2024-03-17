// Fill out your copyright notice in the Description page of Project Settings.


#include "RegisteredAssetCache.h"
#include <NoWhereToRun/Data/LevelDictionary.h>
#include <Blueprint/UserWidget.h>
#include <NoWhereToRun/Enumerations/MapIDS.h>

/// <summary>
/// Clears all user widgets from viewport , typically needed while unloading levels 
/// </summary>
/// <param name="MapID"></param>
/// 
void URegisteredAssetCache::RemoveUIAssetsFromViewport(EMapIDS MapID)
{
    int32 Map = static_cast<int32>(MapID);

    TArray<UUserWidget*>* UserWidgetsArray = RegisteredUICache.Find(Map);
    if (UserWidgetsArray)
    {
        for (UUserWidget* Widget : *UserWidgetsArray)
        {
            Widget->RemoveFromParent();
        }
    }
}

/// <summary>
/// Push the Assets associated with the MapID 
/// </summary>
/// <param name="MapID"></param>
/// <param name="UserWidget"></param>
void URegisteredAssetCache::PushUIToCache(EMapIDS MapID, UUserWidget* const UserWidget)
{
	int32 Map = static_cast<int32>(MapID);

	TArray<UUserWidget*>& UserWidgets = RegisteredUICache.FindOrAdd(Map);
	UserWidgets.Add(UserWidget);
}
