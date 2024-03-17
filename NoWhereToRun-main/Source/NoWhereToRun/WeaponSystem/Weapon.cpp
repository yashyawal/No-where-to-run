// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

EWeaponTypes AWeapon::GetWeaponType() const
{
	return WeaponType;
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}
void AWeapon::Fire_Internal()
{
}
void AWeapon::Fire()
{
	Fire_Internal();
}