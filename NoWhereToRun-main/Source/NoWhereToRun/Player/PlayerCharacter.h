// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Containers/Set.h"
#include "PlayerCharacter.generated.h"
/**
 * Controles player specific properties and states 
*/
class USpringArmComponent;
class UCameraComponent;
class UWeaponManagerComponent;
class UPlayerAnimationInstance;
class UBoxComponent;
class ACollectible;
class UArrowComponent;

UCLASS()
class NOWHERETORUN_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();
	virtual ~APlayerCharacter();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void PossessedBy(AController* NewController) override;

	// Called to bind functionality to input
	USpringArmComponent* GetSpringArm() const;
	UArrowComponent* GetAimCameraArrow() const;
	UCameraComponent* GetCameraComponent() const;
	UWeaponManagerComponent* GetWeaponManagerComponent() const;
	UPlayerAnimationInstance* GetPlayerAnimationInstance() const; 

	UFUNCTION()
	TArray<ACollectible*> GetOverlappingCollectibles();

	//UFUNCTION()
	//TArray<AActor*> GetOverlappingEnimies();

	//UFUNCTION()
	//TArray<AActor*> GetOverlappingEquipMents();

private:
	UPROPERTY()
	TSet<ACollectible*> OverlappedCollectibles;

	/*UPROPERTY()
	TSet<AActor*> OverlappedEnemies;

	UPROPERTY()
	TSet<AActor*> OverlappedEquipMents;*/

	UPROPERTY(EditDefaultsOnly)
	USpringArmComponent* SpringArm;
	
	UPROPERTY(EditDefaultsOnly)
	UCameraComponent* Camera;

	//Holds and manages Weapons
	UPROPERTY(EditDefaultsOnly)
	UWeaponManagerComponent* WeaponManager;

	UPROPERTY()
	UPlayerAnimationInstance* PlayerAnimationInstance;

	//Detects Pickables , enemies etc .
	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* CollisionDetectionComponent;

	UFUNCTION()
	void OnCollisonDetectionComponentOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnCollisonDetectionComponentEndOverlapped(UPrimitiveComponent* OverlappedComponent , AActor* OtherActor , UPrimitiveComponent* OtherComp , int32 OtherBodyIndex);
	 
	UFUNCTION()
	void OnCollectiblesDetectedEvent(ACollectible* Collectible);

	UFUNCTION()
	void OnCollectiblesDetectionEndEvent(ACollectible* Collectible);

	UPROPERTY(EditDefaultsOnly)
	UArrowComponent* AimArrowComponent;

	//UFUNCTION()
	//void OnEnemyDetectedEvent();

	//UFUNCTION()
	//void OnEquipmentDetectedEvent();
};
