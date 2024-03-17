// Fill out your copyright notice in the Description page of Project Settings.


#include "SettingsManager.h"
#include "GameFramework/GameUserSettings.h"

USettingsManager::USettingsManager()
{
}

USettingsManager::~USettingsManager()
{
	GameUserSetting = nullptr;
}

void USettingsManager::CustomInitialize()
{
	//ByDefault setting Graphics quality to Cinematic
	GameUserSetting = UGameUserSettings::GetGameUserSettings();
	GameUserSetting->SetOverallScalabilityLevel(3);
	GameUserSetting->ApplySettings(false);
}
void USettingsManager::SetGraphics(int32 GraphicsQuality)
{
	GameUserSetting->SetOverallScalabilityLevel(GraphicsQuality);
	GameUserSetting->ApplySettings(false);
}

void USettingsManager::EnableVSync(bool bShouldEnableVSync)
{
	GameUserSetting->SetVSyncEnabled(bShouldEnableVSync);
	GameUserSetting->ApplySettings(false);

}
