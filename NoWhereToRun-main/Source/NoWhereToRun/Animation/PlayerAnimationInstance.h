// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include <NoWhereToRun/Enumerations/WeaponType.h>
#include "PlayerAnimationInstance.generated.h"
/**
 * Handles Player animation States
 */
UCLASS()
class NOWHERETORUN_API UPlayerAnimationInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	
	void NativeInitializeAnimation() override;

	UFUNCTION()
	void SetWeaponType(EWeaponTypes SwitchedWeaponType);

	UFUNCTION()
	void SetLeftHandEffectorTransform(const FTransform& HandTransform);

	UFUNCTION()
	void SetLeftHandWeaponHoldIKBlend(float Alpha);

	UFUNCTION()
	void SetShouldFire(bool bShoudFire);

private:
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EWeaponTypes WeaponType;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FTransform DesiredHandTransform;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float LeftHandWeaponHoldIKBlend;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bIsFiring;
};
