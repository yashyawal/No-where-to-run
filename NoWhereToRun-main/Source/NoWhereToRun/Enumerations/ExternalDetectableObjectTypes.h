// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ExternalDetectableObjectTypes.generated.h"
/**
 * Enumerate Objects which can be detected by player
 */
UENUM()
enum class EExternalDetectableObjectTypes : uint8
{
	E_NONE,
	E_COLLECTABLES,
	E_ENEMEY,
	E_EQUIPMENT
};
