// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelManager.h"
#include <NoWhereToRun/Data/LevelDictionary.h>
#include <Kismet/GameplayStatics.h>

// Sets default values
ALevelManager::ALevelManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}
ALevelManager::~ALevelManager()
{
    LevelDictionary = nullptr;
}
void ALevelManager::LoadLevel(EMapIDS MapID)
{
    const auto Map = GetMap(MapID);

    if (Map.IsNull())
    {
        return;
    }

    FLatentActionInfo info;
    info.CallbackTarget = this;
    info.ExecutionFunction = FName("OnRequestedLevelLoaded");
    info.UUID = 0;
    info.Linkage = 0;
    UGameplayStatics::LoadStreamLevelBySoftObjectPtr(GetWorld(), Map, true, true, info);
    
    LoadedMap = MapID;
}

void ALevelManager::UnloadLevel(EMapIDS MapID)
{
    const auto Map = GetMap(MapID);

    if (Map.IsNull())
    {
        return;
    }

    FLatentActionInfo info;
    info.CallbackTarget = this;
    info.ExecutionFunction = FName("OnRequestedLevelUnloaded");
    info.UUID = 1;
    info.Linkage = 1;
    UGameplayStatics::UnloadStreamLevelBySoftObjectPtr(GetWorld(), Map, info, true);
    UnloadedMap = MapID;
}

// Called when the game starts or when spawned
void ALevelManager::BeginPlay()
{
	Super::BeginPlay();
}

void ALevelManager::OnRequestedLevelLoaded()
{
    OnLevelLoadingCompleted.Broadcast(LoadedMap);
}

void ALevelManager::OnRequestedLevelUnloaded()
{
    OnLevelUnloadingCompleted.Broadcast(UnloadedMap);
}

TSoftObjectPtr<UWorld> ALevelManager::GetMap(EMapIDS MapID) const
{
    if (LevelDictionary.IsNull())
    {
        return nullptr;
    }

    int32 MapIndex = static_cast<int32>(MapID);
    // UE_LOG(LogTemp, Warning, TEXT("Level index is %d"), MapIndex);
     //UE_LOG(LogTemp, Warning, TEXT("Level numbers is %d"), LevelDictionary.LoadSynchronous()->Maps.Num());

    return LevelDictionary.LoadSynchronous()->Maps.IsValidIndex(MapIndex) ? LevelDictionary.LoadSynchronous()->Maps[MapIndex] : nullptr;
}

