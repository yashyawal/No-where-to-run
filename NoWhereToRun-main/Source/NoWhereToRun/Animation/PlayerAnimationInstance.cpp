// Fill out your copyright notice in the Description page of Project Settings.
#include "PlayerAnimationInstance.h"

void UPlayerAnimationInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	WeaponType = EWeaponTypes::E_NONE;
}
void UPlayerAnimationInstance::SetWeaponType(EWeaponTypes SwitchedWeaponType)
{
	WeaponType = SwitchedWeaponType;
}

void UPlayerAnimationInstance::SetLeftHandEffectorTransform(const FTransform & HandTransform)
{
	DesiredHandTransform = HandTransform;
}

void UPlayerAnimationInstance::SetLeftHandWeaponHoldIKBlend(float Alpha)
{
	LeftHandWeaponHoldIKBlend = Alpha;
}

void UPlayerAnimationInstance::SetShouldFire(bool bShouldFire)
{
	bIsFiring = bShouldFire;
}
