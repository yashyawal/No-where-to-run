// Fill out your copyright notice in the Description page of Project Settings.


#include "MelleWeapon.h"

// Sets default values
AMelleWeapon::AMelleWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AMelleWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMelleWeapon::Fire_Internal()
{
	Super::Fire_Internal();
	//Perform Attack specific tasks 
}

