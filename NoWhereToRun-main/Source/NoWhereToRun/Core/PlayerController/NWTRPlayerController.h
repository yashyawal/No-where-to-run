// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include <NoWhereToRun/Enumerations/WeaponType.h>
#include "NWTRPlayerController.generated.h"

/**
 * Handles player Inputs
 */
class UInputActionsDictionary;
class UInputMappingContext;
struct FInputActionValue;
class APlayerCharacter;
class AWeapon;

UCLASS()
class NOWHERETORUN_API ANWTRPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ANWTRPlayerController();
	virtual ~ANWTRPlayerController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* PossessedPawn) override;

public:
	// Called to bind functionality to input
	void SetupInputComponent() override;

private:
	UFUNCTION()
	void Look(const FInputActionValue& InputValue);
	
	UFUNCTION()
	void Move(const FInputActionValue& InputValue);
	
	UFUNCTION()
	void AdjustMovementSpeedToRun(const FInputActionValue& InputValue);
	
	UFUNCTION()
	void AdjustMovementSpeedToWalk(const FInputActionValue& InputValue);
	
	UFUNCTION()
	void SwitchToNoWeapon(const FInputActionValue& InputValue);
	
	UFUNCTION()
	void SwitchToPistol(const FInputActionValue& InputValue);
	
	UFUNCTION()
	void SwitchToRifle(const FInputActionValue& InputValue);
	
	UFUNCTION()
	void SwitchToKnife(const FInputActionValue& InputValue);
	
	UFUNCTION()
	void EquipItems(const FInputActionValue& InputValue);

	UFUNCTION()
	void Aim(const FInputActionValue& InputValue);

	UFUNCTION()
	void Fire(const FInputActionValue& InputValue);

	UFUNCTION()
	void RevertAim(const FInputActionValue& InputValue);

	UFUNCTION()
	void StopFiring(const FInputActionValue & InputValue);

	UFUNCTION()
	void SetUpLeftHandIK(APlayerCharacter* ControlledCharacter , EWeaponTypes WeaponType);


	UPROPERTY()
	APlayerCharacter* PlayerCharacter;

	UPROPERTY(EditDefaultsOnly)
	UInputActionsDictionary* InputActionsDictionary;

	UPROPERTY(EditDefaultsOnly)
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditDefaultsOnly)
	float MAX_SPRINGARM_PITCH = 30.0f;

	UPROPERTY(EditDefaultsOnly)
	float MIN_SPRINGARM_PITCH = -30.0f;

	UPROPERTY(EditDefaultsOnly)
	float WALK_SPEED = 143.0f;

	UPROPERTY(EditDefaultsOnly)
	float RUN_SPEED = 500.0f;

	UPROPERTY()
	bool bIsAiming;

	UPROPERTY()
	FVector TargetCameraLocation;

	UPROPERTY()
	FVector CameraOriginalLocation;
};
