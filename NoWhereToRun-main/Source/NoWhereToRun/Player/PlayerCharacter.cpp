// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include <GameFramework/PlayerController.h>
#include "ActorComponents/WeaponManagerComponent.h"
#include <NoWhereToRun/Animation/PlayerAnimationInstance.h>
#include <Components/BoxComponent.h>
#include <NoWhereToRun/DetectableSystem/DetectableObject.h>
#include <NoWhereToRun/DetectableSystem/Collectible.h>
#include <NoWhereToRun/Enumerations/PickableObjectType.h>
#include <Components/ArrowComponent.h>

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	if (!SpringArm)
	{
		SpringArm = CreateDefaultSubobject<USpringArmComponent>(FName("CameraBoom"));
		SpringArm->SetupAttachment(RootComponent);
	}
	if (!Camera)
	{
		Camera = CreateDefaultSubobject<UCameraComponent>(FName("Camera"));
		Camera->SetupAttachment(SpringArm);
	}
	if (!WeaponManager)
	{
		WeaponManager = CreateDefaultSubobject<UWeaponManagerComponent>(FName("WeaponManager"));
	}

	if (!CollisionDetectionComponent)
	{
		CollisionDetectionComponent = CreateDefaultSubobject<UBoxComponent>(FName("CollisionDetectionComponent"));
		CollisionDetectionComponent->SetupAttachment(GetRootComponent());
	}
	if (!AimArrowComponent)
	{
		AimArrowComponent = CreateDefaultSubobject<UArrowComponent>(FName("Camera Aim Arrow Component"));
		AimArrowComponent->SetupAttachment(GetRootComponent());
	}

}
APlayerCharacter::~APlayerCharacter()
{
	OverlappedCollectibles.Empty();
}
// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	PlayerAnimationInstance = Cast<UPlayerAnimationInstance>(GetMesh()->GetAnimInstance());
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	CollisionDetectionComponent->OnComponentBeginOverlap.AddDynamic(this , &APlayerCharacter::OnCollisonDetectionComponentOverlapped);
	CollisionDetectionComponent->OnComponentEndOverlap.AddDynamic(this , &APlayerCharacter::OnCollisonDetectionComponentEndOverlapped);
}

USpringArmComponent* APlayerCharacter::GetSpringArm() const
{
    return SpringArm;
}

UArrowComponent* APlayerCharacter::GetAimCameraArrow() const
{
	return AimArrowComponent;
}

UCameraComponent* APlayerCharacter::GetCameraComponent() const
{
	return Camera;
}

UWeaponManagerComponent* APlayerCharacter::GetWeaponManagerComponent() const
{
	return WeaponManager;
}

UPlayerAnimationInstance* APlayerCharacter::GetPlayerAnimationInstance() const
{
	return PlayerAnimationInstance;
}

TArray<ACollectible*> APlayerCharacter::GetOverlappingCollectibles()
{
	return OverlappedCollectibles.Array();
}

//TArray<AActor*> APlayerCharacter::GetOverlappingEnimies()
//{
//	return TArray<AActor*>();
//}
//
//TArray<AActor*> APlayerCharacter::GetOverlappingEquipMents()
//{
//	return TArray<AActor*>();
//}

void APlayerCharacter::OnCollisonDetectionComponentOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	if (OverlappedComponent == CollisionDetectionComponent && OtherActor!= this )
	{
		//OverlappedActors.Add(OtherActor);
		//UE_LOG(LogTemp, Warning, TEXT("%s"), *Actor->GetName());
		if (const auto DetectedActor = Cast<IDetectableObject>(OtherActor))
		{
			EExternalDetectableObjectTypes DetectedObjectType = DetectedActor->GetDetableObjectType();
			switch (DetectedObjectType)
			{
			case EExternalDetectableObjectTypes::E_COLLECTABLES: //Gets triggered only on weapons and crates
			{
				if (const auto Collectible = Cast<ACollectible>(OtherActor))
				{
					OnCollectiblesDetectedEvent(Collectible);
					OverlappedCollectibles.Add(Collectible);
				}
				break;
			}

			case EExternalDetectableObjectTypes::E_ENEMEY: //Gets triggered only on Enemies .e.g Zombie
			{

				break;
			}
			case EExternalDetectableObjectTypes::E_EQUIPMENT://Gets triggered only on Equipment .e.g PasswordPanel
			{

				break;
			}
			default:
				break;
			}
		}
	}
}

void APlayerCharacter::OnCollisonDetectionComponentEndOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OverlappedComponent == CollisionDetectionComponent)
	{
		

		if (const auto DetectedActor = Cast<IDetectableObject>(OtherActor))
		{
			EExternalDetectableObjectTypes DetectedObjectType = DetectedActor->GetDetableObjectType();
			switch (DetectedObjectType)
			{
			case EExternalDetectableObjectTypes::E_COLLECTABLES: //Gets triggered only on weapons and crates
			{
				if (const auto Collectible = Cast<ACollectible>(OtherActor))
				{
					OnCollectiblesDetectionEndEvent(Collectible);
					OverlappedCollectibles.Remove(Collectible);
				}
				break;
			}

			case EExternalDetectableObjectTypes::E_ENEMEY: //Gets triggered only on Enemies .e.g Zombie
			{

				break;
			}
			case EExternalDetectableObjectTypes::E_EQUIPMENT://Gets triggered only on Equipment .e.g PasswordPanel
			{

				break;
			}
			default:
				break;
			}
		}
	}
}

void APlayerCharacter::OnCollectiblesDetectedEvent(ACollectible* Collectible)
{
	Collectible->ShowDescriptorWidget(true);
	// Do other Related operations regarding on overlap 
}

void APlayerCharacter::OnCollectiblesDetectionEndEvent(ACollectible* Collectible)
{
	Collectible->ShowDescriptorWidget(false);
}