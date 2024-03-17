// Fill out your copyright notice in the Description page of Project Settings.


#include "RangedWeapon.h"

// Sets default values
ARangedWeapon::ARangedWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ARangedWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARangedWeapon::Fire_Internal()
{
	Super::Fire_Internal();
	//Perform Fire specific tasks

}

