// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GlobalGameInstance.generated.h"
class UUIDictionary;
enum  EMapIDS;
class AUIManager;
class ALevelManager;
class USettingsManager;

/**
 * Handles global game attributes , resource handles , and functionalities like level streaming 
 */
UCLASS()
class NOWHERETORUN_API UGlobalGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UFUNCTION()
	AUIManager* GetUIManager() const;

	UFUNCTION()
	ALevelManager* GetLevelManager() const;

	UFUNCTION()
	USettingsManager* GetSettingManager() const;

private:

#pragma region Properties

	void Init() override;
	void Shutdown() override;

	/// <summary>
	/// Listeners to level manager's load/unload level  
	/// </summary>
	/// <param name="MapID"></param>
	UFUNCTION()
	void OnLevelLoaded(EMapIDS MapID);
	UFUNCTION()
	void OnLevelUnloaded(EMapIDS MapID);

#pragma endregion

# pragma region Attributes

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AUIManager> UIManagerAsset;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ALevelManager> LevelManagerAsset;

	UPROPERTY()
	AUIManager* UIManager;

	UPROPERTY()
	ALevelManager* LevelManager;

	UPROPERTY()
	USettingsManager* SettingsManager;

#pragma endregion

};
