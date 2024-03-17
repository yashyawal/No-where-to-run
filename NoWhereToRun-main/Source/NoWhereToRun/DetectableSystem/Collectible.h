// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <NoWhereToRun/DetectableSystem/DetectableObject.h>
#include <NoWhereToRun/Enumerations/PickableObjectType.h>
#include <NoWhereToRun/Enumerations/ExternalDetectableObjectTypes.h>
#include "Collectible.generated.h"
//
class UStaticMeshComponent;
class UBoxComponent;
class UWidgetComponent;

/**
* Base Class for all collectibles
*/

UCLASS()
class NOWHERETORUN_API ACollectible : public AActor , public IDetectableObject
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACollectible();
	virtual ~ACollectible();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION()
	EPickableTypes GetPickableObjectType() const;
	
	EExternalDetectableObjectTypes GetDetableObjectType() const override;
	
	UFUNCTION()
	bool GetIsEquippedByPlayer() const;

	UFUNCTION()
	void SetIsEquippedByPlayer(bool bShouldOwnedByPlayer);

	UFUNCTION()
	void ShowDescriptorWidget(bool bShouldDisplay);

	UFUNCTION()
	UStaticMeshComponent* GetStaticMeshComponent() const;

protected:

	UPROPERTY()
	bool bISOwnedByPlayer;

	//Represents Visible Body of the collectible
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Mesh;
    
	//Represents The pop up desciption over the object
	UPROPERTY(EditDefaultsOnly)
	UWidgetComponent* DescriptorWidget;

	//Represents the type of Collectible
	UPROPERTY(EditDefaultsOnly)
	EPickableTypes PickableObjectType;

	UPROPERTY(VisibleAnywhere)
	EExternalDetectableObjectTypes DetectableObjectType = EExternalDetectableObjectTypes::E_COLLECTABLES;

};
