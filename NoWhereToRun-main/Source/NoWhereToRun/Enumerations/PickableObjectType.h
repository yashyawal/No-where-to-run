// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickableObjectType.generated.h"
/**
 * Types of pickable items Player will find
 */
UENUM(BlueprintType)
enum  class EPickableTypes: uint8 
{
    E_WEAPON,
    E_HEALTHBOOSTER,
    E_PISTOLAMMO,
    E_RIFLEAMMO
};
