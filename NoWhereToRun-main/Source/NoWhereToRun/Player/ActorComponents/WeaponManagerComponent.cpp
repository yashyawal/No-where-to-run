// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponManagerComponent.h"
#include <NoWhereToRun/Enumerations/WeaponType.h>
#include <NoWhereToRun/Player/PlayerCharacter.h>
#include <Components/StaticMeshComponent.h>
#include <Components/SkeletalMeshComponent.h>
#include <NoWhereToRun/WeaponSystem/Weapon.h>

// Sets default values for this component's properties
UWeaponManagerComponent::UWeaponManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


AWeapon* UWeaponManagerComponent::GetWeapon(EWeaponTypes WeaponType) const
{
	AWeapon* Weapon = WeaponInventory.FindRef(WeaponType);
	return Weapon;
}

UWeaponManagerComponent::~UWeaponManagerComponent()
{
	CurrentWeapon = nullptr;
	WeaponInventory.Empty();
}


void UWeaponManagerComponent::PutWeaponInInventory(AWeapon* Weapon, EWeaponTypes WeaponType)
{
	if (Weapon)
	{
		Weapon->GetStaticMeshComponent()->SetGenerateOverlapEvents(false);
		Weapon->GetStaticMeshComponent()->SetVisibility(false);
		Weapon->GetStaticMeshComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		WeaponInventory.FindOrAdd(WeaponType, Weapon);
	}
}

void UWeaponManagerComponent::SetCurrentWeapon(AWeapon* Weapon, EWeaponTypes WeaponType)
{
	CurrentWeaponType = WeaponType;
	if (CurrentWeaponType == EWeaponTypes::E_NONE)
	{
		if (!CurrentWeapon)
		{
			return;
		}
		else
		{
			CurrentWeapon->GetStaticMeshComponent()->SetVisibility(false);
			CurrentWeapon = nullptr;
			return;
		}
	}

	if (CurrentWeapon)
	{
		CurrentWeapon->GetStaticMeshComponent()->SetVisibility(false);
		CurrentWeapon = nullptr;
	}

	CurrentWeapon = Weapon;
	//Wield weapon
	WieldCurrentWeapon(CurrentWeapon, CurrentWeaponType);
	
}

void UWeaponManagerComponent::RemoveCurrentWeaponFromInventory()
{
	CurrentWeapon->GetStaticMeshComponent()->SetGenerateOverlapEvents(true);
	CurrentWeapon->GetStaticMeshComponent()->SetVisibility(true);
	CurrentWeapon->GetStaticMeshComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CurrentWeapon->GetStaticMeshComponent()->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	WeaponInventory.Remove(CurrentWeaponType);
}


EWeaponTypes UWeaponManagerComponent::GetCurrentWeaponType()
{
	return CurrentWeaponType;
}

void UWeaponManagerComponent::EngageWeapon()
{
	if (CurrentWeapon)
	{
		CurrentWeapon->Fire();
	}
}

// Called when the game starts
void UWeaponManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UWeaponManagerComponent::WieldCurrentWeapon(AWeapon* Weapon , EWeaponTypes WeaponType)
{
	if (auto PlayerCharacter = Cast<APlayerCharacter>(GetOwner()))
	{
		USkeletalMeshComponent* PlayerCharacterMesh = PlayerCharacter->GetMesh();
		if (!PlayerCharacterMesh)
		{
			return;
		}
		CurrentWeapon->GetStaticMeshComponent()->SetVisibility(true);

		switch (WeaponType)
		{
			case EWeaponTypes::E_KNIFE:
			{
				Weapon->GetStaticMeshComponent()->AttachToComponent(PlayerCharacterMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, FName("KnifeSocket"));
				break;
			}
			case EWeaponTypes::E_PISTOL:
			{
				Weapon->GetStaticMeshComponent()->AttachToComponent(PlayerCharacterMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, FName("PistolSocket"));
				break;
			}
			case EWeaponTypes::E_RIFLE:
			{
				Weapon->GetStaticMeshComponent()->AttachToComponent(PlayerCharacterMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, FName("RifleSocket"));
				break;
			}
			default:
				break;
		}
	}
}