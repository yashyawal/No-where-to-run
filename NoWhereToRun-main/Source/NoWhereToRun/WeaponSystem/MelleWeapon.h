// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <NoWhereToRun/WeaponSystem/Weapon.h>
#include "MelleWeapon.generated.h"

UCLASS()
class NOWHERETORUN_API AMelleWeapon : public AWeapon
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMelleWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void Fire_Internal() override;
};
