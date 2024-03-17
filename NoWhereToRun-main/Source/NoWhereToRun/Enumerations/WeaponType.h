// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponType.generated.h"
/**
 * Types of weapon which can be weild by the player at any instance of time
 */
UENUM(BlueprintType)
enum  class EWeaponTypes: uint8 
{
	E_NONE,
	E_KNIFE,
	E_PISTOL,
	E_RIFLE
};
