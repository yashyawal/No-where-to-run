// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include <NoWhereToRun/Enumerations/ExternalDetectableObjectTypes.h>
#include "DetectableObject.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UDetectableObject : public UInterface
{
	GENERATED_BODY()
};

/**
 * Differentiates different types of detectable objects
 */
class NOWHERETORUN_API IDetectableObject
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION()
	virtual EExternalDetectableObjectTypes GetDetableObjectType() const = 0;
};
