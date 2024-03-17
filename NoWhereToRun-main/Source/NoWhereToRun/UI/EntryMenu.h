// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EntryMenu.generated.h"
class UButton;
class UWidgetAnimation;
/**
 * Represents UI for entry Menu
 */
UCLASS()
class NOWHERETORUN_API UEntryMenu : public UUserWidget
{
	GENERATED_BODY()
private:

#pragma region Properties
    
	bool Initialize() override;
	void NativeDestruct() override;


#pragma endregion Properties

#pragma region Events
	
	UFUNCTION()
	void OnPlayButtonClicked();

	UFUNCTION()
	void OnOptionButtonClicked();

	UFUNCTION()
	void OnQuitButtonClicked();

	UFUNCTION()
	void OnPlayButtonHovered();

	UFUNCTION()
	void OnOptionButtonHovered();

	UFUNCTION()
	void OnQuitButtonHovered();

	UFUNCTION()
	void OnPlayButtonUnhovered();

	UFUNCTION()
	void OnOptionButtonUnhovered();

	UFUNCTION()
	void OnQuitButtonUnhovered();


#pragma endregion Events

# pragma region Attributes

	UPROPERTY(meta = (BindWidget))
	UButton* PlayButton;
	
	UPROPERTY(meta = (BindWidget))
	UButton* OptionButton;

	UPROPERTY(meta = (BindWidget))
	UButton* QuitButton;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* ScalePlayButton;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* ScaleQuitButton;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* ScaleOptionButton;

# pragma endregion Attributes


	
};
