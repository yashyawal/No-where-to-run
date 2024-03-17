// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OptionMenu.generated.h"

/**
 * Holds Settings Which can be changed by user in runtime
 */

class UComboBoxString;
class UCheckBox;
class USettingsManager;
class UButton;

UCLASS()
class NOWHERETORUN_API UOptionMenu : public UUserWidget
{
	GENERATED_BODY()

private:
	//TODO: This can be replaced by a widget as the buttons and quality types remains same 
#pragma region Attributes

	UPROPERTY(meta = (BindWidget))
	UComboBoxString* QualityOptionsComboBox;

	UPROPERTY(meta = (BindWidget))
	UCheckBox* VSyncCheckBox;

	UPROPERTY(meta = (BindWidget))
	UButton* BackButton;

	UPROPERTY()
	USettingsManager* SettingsManager;

#pragma endregion
#pragma region Properties

	bool Initialize() override;

	UFUNCTION()
	void OnQualitySelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionInfo);

    UFUNCTION()
	void OnVSyncChecked(bool bIsChecked);

	UFUNCTION()
	void OnBackButtonClicked();

#pragma endregion
};