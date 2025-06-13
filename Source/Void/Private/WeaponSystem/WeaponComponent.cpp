// Copyright Epic Games, Inc. All Rights Reserved.


#include "WeaponSystem/WeaponComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "WeaponSystem/Weapon.h"

// Sets default values for this component's properties
UWeaponComponent::UWeaponComponent()
{
	
}

void UWeaponComponent::AttachWeapon(AWeapon* NewWeapon)
{
	if (!Player) return;
	Weapon = NewWeapon;

	// Attach new weapon to player
	const FAttachmentTransformRules AttachmentRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true);
	bool bAttached = Weapon->AttachToComponent(Player->GetMesh1P(), AttachmentRules, WeaponSocket);
	UE_LOG(LogBlueprint, Warning, TEXT("Attachment succesful:  %hhd"), bAttached)
	
	Player->SetHasRifle(true);
	
	// Set up action bindings
	if (APlayerController* PlayerController = Cast<APlayerController>(Player->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			// Set the priority of the mapping to 1, so that it overrides the Jump action with the Fire action when using touch input
			Subsystem->AddMappingContext(FireMappingContext, 1);
		}

		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
		{
			// Fire
			EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &UWeaponComponent::Shoot);
		}
	}
}

AWeapon* UWeaponComponent::GetWeapon()
{
	return Weapon;
}

void UWeaponComponent::Shoot()
{
	if (Weapon) Weapon->Shoot();
}

void UWeaponComponent::InitWithPlayer(AVoidCharacter* OwningPlayer)
{
	this->Player = OwningPlayer;
}