// Fill out your copyright notice in the Description page of Project Settings.
#include "UIManager.h"
#include <NoWhereToRun/Data/UIDictionary.h>
#include <NowhereToRun/Core/GameInstance/GlobalGameInstance.h>
#include <NoWhereToRun/Enumerations/MapIDS.h>
#include <NoWhereToRun/UI/EntryMenu.h>
#include <NoWhereToRun/UI/OptionMenu.h>
#include <Blueprint/UserWidget.h>

// Sets default values
AUIManager::AUIManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

AUIManager::~AUIManager()
{
    EntryMenu = nullptr;
    OptionMenu = nullptr;
    CrossHair = nullptr;
}
// Called when the game starts or when spawned
void AUIManager::BeginPlay()
{
    Super::BeginPlay();
    UIDictionary.LoadSynchronous();

    const auto PlayerController = GetWorld()->GetFirstPlayerController();
    if (!PlayerController)
    {
        return;
    }
    //Create and cache all necessary Widgets
    EntryMenu = Cast<UEntryMenu>(CreateWidget(PlayerController, UIDictionary->EntryMenuUIAsset));
    OptionMenu = Cast<UOptionMenu>(CreateWidget(PlayerController, UIDictionary->OptionMenuUIAsset));
    CrossHair = Cast<UUserWidget>(CreateWidget(PlayerController, UIDictionary->CrossHairUIAsset));
}

void AUIManager::AddWidgetsToViewport(EMapIDS MapIDS)
{
    switch (MapIDS)
    {
        case E_EntryStage:
        {
            if (EntryMenu)
            {
                EntryMenu->AddToViewport();
            }
            break;
        }
        case E_STAGE1:
        {
            break;
        }
        case E_STAGE2:
        {
            break;
        }
    }
}

void AUIManager::RemoveWidgetsFromViewport(EMapIDS MapIDS)
{
    switch (MapIDS)
    {
        case E_EntryStage:
        {
            if (EntryMenu)
            {
                EntryMenu->RemoveFromParent();
            }
            break;
        }
        case E_STAGE1:
        {
            break;
        }
        case E_STAGE2:
        {
            break;
        }
    }
}

void AUIManager::AddOptionMenu()
{
    if (!OptionMenu->IsInViewport())
    {
        OptionMenu->AddToViewport();
    }
    OptionMenu->SetVisibility(ESlateVisibility::Visible);
}

void AUIManager::RemoveOptionMenu()
{
    if (OptionMenu)
    {
        OptionMenu->SetVisibility(ESlateVisibility::Collapsed);
    }
}

void AUIManager::AddCrossHair()
{
    if (!CrossHair->IsInViewport())
    {
        CrossHair->AddToViewport();
    }
    CrossHair->SetVisibility(ESlateVisibility::Visible);
}

void AUIManager::RemoveCrossHair()
{
    if (CrossHair)
    {
        CrossHair->SetVisibility(ESlateVisibility::Collapsed);
    }
}
