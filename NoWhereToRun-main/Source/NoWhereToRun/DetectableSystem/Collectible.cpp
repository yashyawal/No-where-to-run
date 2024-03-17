// Fill out your copyright notice in the Description page of Project Settings.

#include "Collectible.h"
#include <Components/StaticMeshComponent.h>
#include <Components/WidgetComponent.h>
#include <Components/BoxComponent.h>
// Sets default values
ACollectible::ACollectible()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	if (!Mesh)
	{
		Mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticMesh"));
	}
	if (!DescriptorWidget)
	{
		DescriptorWidget = CreateDefaultSubobject<UWidgetComponent>(FName("DescriptionWidget"));
		DescriptorWidget->SetupAttachment(Mesh);
	}

}
ACollectible::~ACollectible()
{
	Mesh = nullptr;
	DescriptorWidget = nullptr;
}
// Called when the game starts or when spawned
void ACollectible::BeginPlay()
{
	Super::BeginPlay();
	
}

EPickableTypes ACollectible::GetPickableObjectType() const
{
	return PickableObjectType;
}

EExternalDetectableObjectTypes ACollectible::GetDetableObjectType() const
{
	return DetectableObjectType;
}

bool ACollectible::GetIsEquippedByPlayer() const
{
	return bISOwnedByPlayer;
}

void ACollectible::SetIsEquippedByPlayer(bool bShouldOwnedByPlayer)
{
	bISOwnedByPlayer = bShouldOwnedByPlayer;
}

void ACollectible::ShowDescriptorWidget(bool bShouldDisplay)
{
	DescriptorWidget->SetVisibility(bShouldDisplay);
}

UStaticMeshComponent* ACollectible::GetStaticMeshComponent() const
{
	return Mesh;
}
