// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <NoWhereToRun/Enumerations/WeaponType.h>
#include "WeaponManagerComponent.generated.h"

class AWeapon;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NOWHERETORUN_API UWeaponManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponManagerComponent();
	~UWeaponManagerComponent();

	UFUNCTION()
	AWeapon* GetWeapon(EWeaponTypes WeaponType) const;

	UFUNCTION()
	void PutWeaponInInventory(AWeapon* Weapon, EWeaponTypes WeaponType);

	UFUNCTION()
	void SetCurrentWeapon(AWeapon* Weapon , EWeaponTypes WeaponType);

	UFUNCTION()
	void RemoveCurrentWeaponFromInventory();

	UFUNCTION()
	EWeaponTypes GetCurrentWeaponType();

	//Engages current weapon , triggers the fire event of currently weield weapons
	UFUNCTION()
	void EngageWeapon();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TMap<EWeaponTypes, AWeapon*> WeaponInventory;
	
	UPROPERTY()
	EWeaponTypes CurrentWeaponType;

	UPROPERTY()
	AWeapon* CurrentWeapon;

	UFUNCTION()
	void WieldCurrentWeapon( AWeapon* Weapon , EWeaponTypes WeaponType);
};
