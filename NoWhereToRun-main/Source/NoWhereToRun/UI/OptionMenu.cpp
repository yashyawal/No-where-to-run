// Fill out your copyright notice in the Description page of Project Settings.
#include "OptionMenu.h"
#include <Components/CheckBox.h>
#include <Components/ComboBoxString.h>
#include <NoWhereToRun/Core/GameInstance/GlobalGameInstance.h>
#include <NoWhereToRun/Settings/SettingsManager.h>
#include <NoWhereToRun/UI/UIManager.h>
#include <Components/Button.h>
bool UOptionMenu::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}

	if (QualityOptionsComboBox)
	{
		QualityOptionsComboBox->OnSelectionChanged.AddDynamic(this, &UOptionMenu::OnQualitySelectionChanged);
	}

	if (VSyncCheckBox)
	{
		VSyncCheckBox->OnCheckStateChanged.AddDynamic(this, &UOptionMenu::OnVSyncChecked);
	}

	if (BackButton)
	{
		BackButton->OnClicked.AddDynamic(this, &UOptionMenu::OnBackButtonClicked);
	}

	if (!SettingsManager)
	{
		if (const auto GameInstance = Cast<UGlobalGameInstance>(GetGameInstance()))
		{
			SettingsManager = GameInstance->GetSettingManager();
		}
	}
	return true;
}

void UOptionMenu::OnQualitySelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionInfo)
{
	if (!SettingsManager)
	{
		return;
	}
	//TODO : Find a better way to elemenate String as argument in OnQualitySelectionChanged, May be replace with an enum with a custom made UI hirarchy
	if (SelectedItem.Equals("LOW"))
	{
		SettingsManager->SetGraphics(0);
	}
	if (SelectedItem.Equals("MEDIUM"))
	{
		SettingsManager->SetGraphics(1);
	}
	if (SelectedItem.Equals("HIGH"))
	{
		SettingsManager->SetGraphics(2);
	}
	if (SelectedItem.Equals("EPIC"))
	{
		SettingsManager->SetGraphics(3);
	}
	if (SelectedItem.Equals("CINEMATIC"))
	{
		SettingsManager->SetGraphics(4);
	}
}

void UOptionMenu::OnVSyncChecked(bool bIsChecked)
{
	SettingsManager->EnableVSync(bIsChecked);
}

void UOptionMenu::OnBackButtonClicked()
{
	if (const auto GameInstance = Cast<UGlobalGameInstance>(GetWorld()->GetGameInstance()))
	{
		GameInstance->GetUIManager()->RemoveOptionMenu();
	}
}
