// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <NoWhereToRun/DetectableSystem/Collectible.h>
#include <NoWhereToRun/Enumerations/WeaponType.h>
#include "Weapon.generated.h"

UCLASS()
class NOWHERETORUN_API AWeapon : public ACollectible
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

	UFUNCTION()
	EWeaponTypes GetWeaponType() const;

	UFUNCTION()
	void Fire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void Fire_Internal();

	UPROPERTY(EditDefaultsOnly)
	EWeaponTypes WeaponType;
};