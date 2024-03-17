// Fill out your copyright notice in the Description page of Project Settings.


#include "GlobalGameInstance.h"
#include <NowhereToRun/UI/UIManager.h>
#include <NoWhereToRun/Level/LevelManager.h>
#include <NoWhereToRun/Settings/SettingsManager.h>

ALevelManager* UGlobalGameInstance::GetLevelManager() const
{
    return LevelManager;
}

USettingsManager* UGlobalGameInstance::GetSettingManager() const
{
    return SettingsManager;
}

AUIManager* UGlobalGameInstance::GetUIManager() const
{
    return UIManager;
}

void UGlobalGameInstance::Init()
{
    Super::Init();
    //Create Global managers handles
    if (UIManagerAsset)
    {
        UIManager = GetWorld()->SpawnActor<AUIManager>(UIManagerAsset);
    }
    if (LevelManagerAsset)
    {
        LevelManager = GetWorld()->SpawnActor<ALevelManager>(LevelManagerAsset);
        LevelManager->OnLevelLoadingCompleted.AddDynamic(this, &UGlobalGameInstance::OnLevelLoaded);
        LevelManager->OnLevelUnloadingCompleted.AddDynamic(this, &UGlobalGameInstance::OnLevelUnloaded);

    }
    if (!SettingsManager)
    {
        SettingsManager = NewObject<USettingsManager>();
        SettingsManager->CustomInitialize();
    }
}


void UGlobalGameInstance::Shutdown()
{
    Super::Shutdown();
    UIManager = nullptr;
    LevelManager = nullptr;
    SettingsManager = nullptr;

}

void UGlobalGameInstance::OnLevelLoaded(EMapIDS MapID)
{
    UIManager->AddWidgetsToViewport(MapID);
}

void UGlobalGameInstance::OnLevelUnloaded(EMapIDS MapID)
{
    UIManager->RemoveWidgetsFromViewport(MapID);
}
