// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SettingsManager.generated.h"
/**
 * Controles Game Settings for graphics , audio etc.
 */
class UGameUserSettings;

UCLASS()
class NOWHERETORUN_API USettingsManager : public UObject
{
	GENERATED_BODY()

private:
	
	UPROPERTY()
	UGameUserSettings* GameUserSetting;

public:
	USettingsManager();
	virtual ~USettingsManager();

	UFUNCTION()
	void CustomInitialize();

	UFUNCTION()
	void SetGraphics(int32 GraphicsQuality);

	UFUNCTION()
	void EnableVSync(bool bShouldEnableVSync);
};
