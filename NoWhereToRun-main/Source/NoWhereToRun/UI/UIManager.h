// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UIManager.generated.h"

/// <summary>
/// Create and pushes all the User Widgets required and pushes to Cache
/// </summary>
class UUIDictionary;
class UEntryMenu;
class UOptionMenu;
enum  EMapIDS;

UCLASS()
class NOWHERETORUN_API AUIManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUIManager();
	virtual ~AUIManager();

	/// <summary>
	/// Clears the widgets from viewport related to the level ID passed
	/// </summary>
	/// <param name="MapIDS"></param>
	void AddWidgetsToViewport(EMapIDS MapIDS);

	/// <summary>
	/// Clears the widgets from viewport related to the level ID passed
	/// </summary>
	/// <param name="MapIDS"></param>
	void RemoveWidgetsFromViewport(EMapIDS MapIDS);
	
	void AddOptionMenu();
	void RemoveOptionMenu();

	void AddCrossHair();
	void RemoveCrossHair();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	UPROPERTY()
	UEntryMenu* EntryMenu;

	UPROPERTY()
	UOptionMenu* OptionMenu;

	UPROPERTY()
	UUserWidget* CrossHair;

	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UUIDictionary> UIDictionary;

};
