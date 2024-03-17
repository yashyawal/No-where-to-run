// Fill out your copyright notice in the Description page of Project Settings.


#include "NWTRPlayerController.h"
#include <NoWhereToRun/Player/PlayerCharacter.h>
#include <GameFramework/CharacterMovementComponent.h>
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include <NoWhereToRun/Data/InputActionsDictionary.h>
#include <Kismet/KismetMathLibrary.h>
#include <GameFramework/SpringArmComponent.h>
#include <NoWhereToRun/Animation/PlayerAnimationInstance.h>
#include <NoWhereToRun/Enumerations/PickableObjectType.h>
#include <NoWhereToRun/DetectableSystem/Collectible.h>
#include <NoWhereToRun/Player/ActorComponents/WeaponManagerComponent.h>
#include <NoWhereToRun/WeaponSystem/Weapon.h>
#include <NoWhereToRun/UI/UIManager.h>
#include <NoWhereToRun/Core/GameInstance/GlobalGameInstance.h>
#include <Components/ArrowComponent.h>
#include <Camera/CameraComponent.h>

ANWTRPlayerController::ANWTRPlayerController()
{

}

ANWTRPlayerController::~ANWTRPlayerController()
{
    InputMappingContext = nullptr;
    InputActionsDictionary = nullptr;
    PlayerCharacter = nullptr;
}

void ANWTRPlayerController::BeginPlay()
{
    Super::BeginPlay();

}

void ANWTRPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
    // Get the local player subsystem
    if (const auto LocalPlayer = GetLocalPlayer())
    {
        // Clear out existing mapping, and add our mapping
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer))
        {
            Subsystem->ClearAllMappings();
            Subsystem->AddMappingContext(InputMappingContext, 0);

            if (UEnhancedInputComponent* EnhancedPlayerInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
            {
                EnhancedPlayerInputComponent->BindAction(InputActionsDictionary->InputMove, ETriggerEvent::Triggered, this, &ANWTRPlayerController::Move);
                EnhancedPlayerInputComponent->BindAction(InputActionsDictionary->InputLook, ETriggerEvent::Triggered, this, &ANWTRPlayerController::Look);
                EnhancedPlayerInputComponent->BindAction(InputActionsDictionary->InputSprint, ETriggerEvent::Triggered, this, &ANWTRPlayerController::AdjustMovementSpeedToRun);
                EnhancedPlayerInputComponent->BindAction(InputActionsDictionary->InputSprint, ETriggerEvent::Completed, this, &ANWTRPlayerController::AdjustMovementSpeedToWalk);
                EnhancedPlayerInputComponent->BindAction(InputActionsDictionary->InputSprint, ETriggerEvent::Canceled, this, &ANWTRPlayerController::AdjustMovementSpeedToWalk);
                EnhancedPlayerInputComponent->BindAction(InputActionsDictionary->InputSwitchToNoWeapon, ETriggerEvent::Triggered, this, &ANWTRPlayerController::SwitchToNoWeapon);
                EnhancedPlayerInputComponent->BindAction(InputActionsDictionary->InputSwitchToKnife, ETriggerEvent::Triggered, this, &ANWTRPlayerController::SwitchToKnife);
                EnhancedPlayerInputComponent->BindAction(InputActionsDictionary->InputSwitchToPistol, ETriggerEvent::Triggered, this, &ANWTRPlayerController::SwitchToPistol);
                EnhancedPlayerInputComponent->BindAction(InputActionsDictionary->InputSwitchToRifle, ETriggerEvent::Triggered, this, &ANWTRPlayerController::SwitchToRifle);
                EnhancedPlayerInputComponent->BindAction(InputActionsDictionary->InputEquipCollectibles, ETriggerEvent::Triggered, this, &ANWTRPlayerController::EquipItems);
                EnhancedPlayerInputComponent->BindAction(InputActionsDictionary->InputAim, ETriggerEvent::Triggered, this, &ANWTRPlayerController::Aim);
                EnhancedPlayerInputComponent->BindAction(InputActionsDictionary->InputAim, ETriggerEvent::Completed, this, &ANWTRPlayerController::RevertAim);
                EnhancedPlayerInputComponent->BindAction(InputActionsDictionary->InputAim, ETriggerEvent::Canceled, this, &ANWTRPlayerController::RevertAim);
                EnhancedPlayerInputComponent->BindAction(InputActionsDictionary->InputFire, ETriggerEvent::Triggered, this, &ANWTRPlayerController::Fire);
                EnhancedPlayerInputComponent->BindAction(InputActionsDictionary->InputFire, ETriggerEvent::Completed, this, &ANWTRPlayerController::StopFiring);

            }
        }
    }
}

void ANWTRPlayerController::OnPossess(APawn* PossessedPawn)
{
    Super::OnPossess(PossessedPawn);

    if (PossessedPawn)
    {
        PlayerCharacter = Cast<APlayerCharacter>(PossessedPawn);
        PlayerCharacter->GetCharacterMovement()->MaxWalkSpeed = WALK_SPEED;
        CameraOriginalLocation = PlayerCharacter->GetCameraComponent()->GetRelativeLocation();

    }

}

void ANWTRPlayerController::Look(const FInputActionValue& InputValue)
{
    if (PlayerCharacter)
    {
      const FVector2D LookValue = InputValue.Get<FVector2D>();
      //Clamp pitch rotation of SpringArm
      if (LookValue.X != 0)
      {
          PlayerCharacter->AddControllerYawInput(LookValue.X);
      }
      //Instead of inheriting the Pitch of controller calculate and clamp the spring arms relative rotation
      if (LookValue.Y != 0)
      {
          FRotator SpringArmRotation = PlayerCharacter->GetSpringArm()->GetRelativeRotation();

          SpringArmRotation.Pitch += LookValue.Y;
          SpringArmRotation.Pitch = FMath::Clamp(SpringArmRotation.Pitch, MIN_SPRINGARM_PITCH, MAX_SPRINGARM_PITCH);
          PlayerCharacter->GetSpringArm()->SetRelativeRotation(SpringArmRotation);
      }
    }
}

void ANWTRPlayerController::Move(const FInputActionValue& InputValue)
{
    if (PlayerCharacter)
    {
        const FVector2D MoveValue = InputValue.Get<FVector2D>();
        // Left/Right direction
        if (MoveValue.X != 0.f)
        {
            // Get Right vector
            const FVector Direction = UKismetMathLibrary::GetRightVector(GetControlRotation());//.Roll, 0, GetControlRotation().Yaw));
            PlayerCharacter->AddMovementInput(Direction, MoveValue.X);

        }

        // Forward/Backward direction
        if (MoveValue.Y != 0.f)
        {
            // Get right vector
            const FVector Direction = UKismetMathLibrary::GetForwardVector(GetControlRotation());
            PlayerCharacter->AddMovementInput(Direction, MoveValue.Y);
        }
    }
}

void ANWTRPlayerController::AdjustMovementSpeedToRun(const FInputActionValue& InputValue)
{
    if (PlayerCharacter)
    {
        PlayerCharacter->GetCharacterMovement()->MaxWalkSpeed = RUN_SPEED;
    }
}

void ANWTRPlayerController::AdjustMovementSpeedToWalk(const FInputActionValue& InputValue)
{
    if (PlayerCharacter)
    {
        PlayerCharacter->GetCharacterMovement()->MaxWalkSpeed = WALK_SPEED;
    }
}

void ANWTRPlayerController::SwitchToNoWeapon(const FInputActionValue& InputValue)
{
    if (PlayerCharacter)
    {
        PlayerCharacter->GetPlayerAnimationInstance()->SetLeftHandWeaponHoldIKBlend(0.0f);
        PlayerCharacter->GetPlayerAnimationInstance()->SetWeaponType(EWeaponTypes::E_NONE);
        PlayerCharacter->GetWeaponManagerComponent()->SetCurrentWeapon(nullptr , EWeaponTypes::E_NONE);
    }
}

void ANWTRPlayerController::SwitchToPistol(const FInputActionValue& InputValue)
{
    if (PlayerCharacter)
    {
        if (AWeapon* Weapon = PlayerCharacter->GetWeaponManagerComponent()->GetWeapon(EWeaponTypes::E_PISTOL))
        {
            SetUpLeftHandIK(PlayerCharacter, EWeaponTypes::E_PISTOL);
            PlayerCharacter->GetPlayerAnimationInstance()->SetWeaponType(EWeaponTypes::E_PISTOL);
            PlayerCharacter->GetWeaponManagerComponent()->SetCurrentWeapon(Weapon , EWeaponTypes::E_PISTOL);
        }
    }
}

void ANWTRPlayerController::SwitchToRifle(const FInputActionValue& InputValue)
{
    if (PlayerCharacter)
    {
        if (AWeapon* Weapon = PlayerCharacter->GetWeaponManagerComponent()->GetWeapon(EWeaponTypes::E_RIFLE))
        {
            SetUpLeftHandIK(PlayerCharacter, EWeaponTypes::E_RIFLE);
            PlayerCharacter->GetPlayerAnimationInstance()->SetWeaponType(EWeaponTypes::E_RIFLE);
            PlayerCharacter->GetWeaponManagerComponent()->SetCurrentWeapon(Weapon , EWeaponTypes::E_RIFLE);
        }
    }
}

void ANWTRPlayerController::SwitchToKnife(const FInputActionValue& InputValue)
{
    if (PlayerCharacter)
    {
        if (AWeapon * Weapon = PlayerCharacter->GetWeaponManagerComponent()->GetWeapon(EWeaponTypes::E_KNIFE))
        {
            PlayerCharacter->GetPlayerAnimationInstance()->SetLeftHandWeaponHoldIKBlend(0.0f);
            PlayerCharacter->GetPlayerAnimationInstance()->SetWeaponType(EWeaponTypes::E_KNIFE);
            PlayerCharacter->GetWeaponManagerComponent()->SetCurrentWeapon(Weapon , EWeaponTypes::E_KNIFE);
        }
    }
}

void ANWTRPlayerController::EquipItems(const FInputActionValue& InputValue)
{
    if (PlayerCharacter)
    {
        UWeaponManagerComponent* WeaponManager = PlayerCharacter->GetWeaponManagerComponent();
        if (!WeaponManager)
        {
            return;
        }

        TArray<ACollectible*> OverlappingActors = PlayerCharacter->GetOverlappingCollectibles();
        for (auto Collectible : OverlappingActors)
        {
            EPickableTypes PickableObjectType = Collectible->GetPickableObjectType();
            switch (PickableObjectType)
            {
                // Puts Weapons in weapon Inventory
                case EPickableTypes::E_WEAPON :
                {
                    if (AWeapon* Weapon = Cast<AWeapon>(Collectible))
                    {
                        Weapon->ShowDescriptorWidget(false);
                        WeaponManager->PutWeaponInInventory(Weapon, Weapon->GetWeaponType());
                    }
                    break;
                }

                case EPickableTypes::E_HEALTHBOOSTER:
                {
                    break;
                }
                case EPickableTypes::E_PISTOLAMMO:
                {
                    break;
                }
                case EPickableTypes::E_RIFLEAMMO:
                {
                    break;
                }
                default:
                    break;
            }

        }
    }
}

void ANWTRPlayerController::Aim(const FInputActionValue& InputValue)
{
    if (PlayerCharacter)
    {
        //Cache the Aim position for camera 
        if (auto AimArrow = PlayerCharacter->GetAimCameraArrow())
        {
            TargetCameraLocation = AimArrow->GetRelativeLocation();
            PlayerCharacter->GetCameraComponent()->SetRelativeLocation(TargetCameraLocation);
            PlayerCharacter->GetCameraComponent()->SetRelativeRotation(FRotator(0, 0, 0));
            bIsAiming = true;
        }
        if (const auto GameInstance = Cast<UGlobalGameInstance>(GetWorld()->GetGameInstance()))
        {
            GameInstance->GetUIManager()->AddCrossHair();
        }
    }
}


void ANWTRPlayerController::Fire(const FInputActionValue& InputValue)
{
    // Tell weapon manager to shoot the current weapon
    // Tell animation instance to play shoot animation
    if (PlayerCharacter && PlayerCharacter->GetWeaponManagerComponent()->GetCurrentWeaponType() != EWeaponTypes::E_NONE)
    {
       // PlayerCharacter->GetWeaponManagerComponent()->EngageWeapon();
        //Considering the current weapon is already being set in the switch to call
        PlayerCharacter->GetPlayerAnimationInstance()->SetShouldFire(true);
    }
}

void ANWTRPlayerController::RevertAim(const FInputActionValue& InputValue)
{
    if (PlayerCharacter)
    {
        //Remove cross hair
        if (const auto GameInstance = Cast<UGlobalGameInstance>(GetWorld()->GetGameInstance()))
        {
            GameInstance->GetUIManager()->RemoveCrossHair();
        }
        // Unzoom the camera to the original position 
        PlayerCharacter->GetCameraComponent()->SetRelativeLocation(CameraOriginalLocation);
    }
}

void ANWTRPlayerController::StopFiring(const FInputActionValue& InputValue)
{
    // Tell weapon manager to stop firing the current weapon
   // Tell animation instance to stop playing Firing animation
    if (PlayerCharacter && PlayerCharacter->GetWeaponManagerComponent()->GetCurrentWeaponType() != EWeaponTypes::E_NONE)
    {
        // PlayerCharacter->GetWeaponManagerComponent()->EngageWeapon();
         //Considering the current weapon is already being set in the switch to call
        PlayerCharacter->GetPlayerAnimationInstance()->SetShouldFire(false);
    }
}

void ANWTRPlayerController::SetUpLeftHandIK(APlayerCharacter* ControlledCharacter, EWeaponTypes WeaponType)
{
      //TODO Find a way to calculate offset between effector bone and the tip for FABRIK
      //The offset is now hard coded which comes from testing and iteration
       ControlledCharacter->GetPlayerAnimationInstance()->SetLeftHandWeaponHoldIKBlend(1.0f);
       switch (WeaponType)
       {
       case EWeaponTypes::E_PISTOL:
       {
           ControlledCharacter->GetPlayerAnimationInstance()->SetLeftHandEffectorTransform(FTransform(FVector(-2.253f, -6.123f, 5.625f)));
           break;
       }
       case EWeaponTypes::E_RIFLE:
       {
           ControlledCharacter->GetPlayerAnimationInstance()->SetLeftHandEffectorTransform(FTransform(FVector(5.465f, -44.323f, 10.174f)));
           break;
       }
       default:
           break;
       }

}
