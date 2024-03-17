// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <NoWhereToRun/Enumerations/MapIDS.h>
#include "LevelManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelLoadingCompleteDelegate, EMapIDS, MapID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelUnloadingCompleteDelegate, EMapIDS, MapID);


/// <summary>
/// Handels Level Streaming 
/// </summary>
class ULevelDictionary;
UCLASS()
class NOWHERETORUN_API ALevelManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelManager();
	virtual ~ALevelManager();

	UFUNCTION()
	void LoadLevel(EMapIDS MapID);

	UFUNCTION()
	void UnloadLevel(EMapIDS MapID);

	UPROPERTY()
	FOnLevelLoadingCompleteDelegate OnLevelLoadingCompleted;

	UPROPERTY()
	FOnLevelUnloadingCompleteDelegate OnLevelUnloadingCompleted;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	
	UFUNCTION()
	void OnRequestedLevelLoaded();

	UFUNCTION()
	void OnRequestedLevelUnloaded();

	UFUNCTION()
	TSoftObjectPtr<UWorld> GetMap(EMapIDS MapID) const;

	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<ULevelDictionary> LevelDictionary;

	EMapIDS LoadedMap , UnloadedMap;

};
