// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InputAction.h"
#include "InputActionsDictionary.generated.h"

/**
 * Holds Input Actions , can be changed dynamically by user 
 */
UCLASS()
class NOWHERETORUN_API UInputActionsDictionary : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditDefaultsOnly)
	UInputAction* InputMove;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* InputLook;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* InputSprint;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* InputSwitchToNoWeapon;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* InputSwitchToKnife;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* InputSwitchToPistol;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* InputSwitchToRifle;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* InputEquipCollectibles;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* InputAim;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* InputFire;

};
