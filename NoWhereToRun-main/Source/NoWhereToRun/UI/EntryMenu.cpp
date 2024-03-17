// Fill out your copyright notice in the Description page of Project Settings.


#include "EntryMenu.h"
#include <Components/Button.h>
#include <Kismet/KismetSystemLibrary.h>
#include <NoWhereToRun/Core/GameInstance/GlobalGameInstance.h>
#include <NoWhereToRun/Enumerations/MapIDS.h>
#include <NoWhereToRun/Level/LevelManager.h>
#include <NoWhereToRun/UI/UIManager.h>
#include <Animation/WidgetAnimation.h>

bool UEntryMenu::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}

	if (PlayButton->IsValidLowLevel())
	{
		PlayButton->OnClicked.AddDynamic(this, &UEntryMenu::OnPlayButtonClicked);
		PlayButton->OnHovered.AddDynamic(this, &UEntryMenu::OnPlayButtonHovered);
		PlayButton->OnUnhovered.AddDynamic(this, &UEntryMenu::OnPlayButtonUnhovered);

	}

	if (OptionButton->IsValidLowLevel())
	{
		OptionButton->OnClicked.AddDynamic(this, &UEntryMenu::OnOptionButtonClicked);
		OptionButton->OnHovered.AddDynamic(this, &UEntryMenu::OnOptionButtonHovered);
		OptionButton->OnUnhovered.AddDynamic(this, &UEntryMenu::OnOptionButtonUnhovered);


	}

	if (QuitButton->IsValidLowLevel())
	{
		QuitButton->OnClicked.AddDynamic(this, &UEntryMenu::OnQuitButtonClicked);
		QuitButton->OnHovered.AddDynamic(this, &UEntryMenu::OnQuitButtonHovered);
		QuitButton->OnUnhovered.AddDynamic(this, &UEntryMenu::OnQuitButtonUnhovered);


	}

	return true;

}
void UEntryMenu::NativeDestruct()
{
	Super::NativeDestruct();

	PlayButton = nullptr;
	QuitButton = nullptr;
	OptionButton = nullptr;

}

void UEntryMenu::OnPlayButtonClicked()
{
	UGlobalGameInstance* GlobalGameInstance = Cast<UGlobalGameInstance>(GetWorld()->GetGameInstance());
	if (GlobalGameInstance)
	{
		GlobalGameInstance->GetLevelManager()->UnloadLevel(EMapIDS::E_EntryStage);
		GlobalGameInstance->GetLevelManager()->LoadLevel(EMapIDS::E_STAGE1);
	}
}

void UEntryMenu::OnOptionButtonClicked()
{
	UGlobalGameInstance* GlobalGameInstance = Cast<UGlobalGameInstance>(GetWorld()->GetGameInstance());
	if (GlobalGameInstance)
	{
		GlobalGameInstance->GetUIManager()->AddOptionMenu();
	}
}

void UEntryMenu::OnQuitButtonClicked()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
}

void UEntryMenu::OnPlayButtonHovered()
{
	PlayAnimationForward(ScalePlayButton);
}

void UEntryMenu::OnOptionButtonHovered()
{
	PlayAnimationForward(ScaleOptionButton);
}

void UEntryMenu::OnQuitButtonHovered()
{
	PlayAnimationForward(ScaleQuitButton);
}

void UEntryMenu::OnPlayButtonUnhovered()
{
	PlayAnimationReverse(ScalePlayButton);
}

void UEntryMenu::OnOptionButtonUnhovered()
{
	PlayAnimationReverse(ScaleOptionButton);
}

void UEntryMenu::OnQuitButtonUnhovered()
{
	PlayAnimationReverse(ScaleQuitButton);
}
