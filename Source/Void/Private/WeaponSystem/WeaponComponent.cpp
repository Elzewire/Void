// Copyright Epic Games, Inc. All Rights Reserved.


#include "WeaponSystem/WeaponComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
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
	if (!FireAction || !FireMappingContext) return;
	if (APlayerController* PlayerController = Cast<APlayerController>(Player->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			// Remove old
			if (FireMappingContext) Subsystem->RemoveMappingContext(FireMappingContext);

			// Add new
			FireMappingContext = Weapon->GetFireMappingContext();
			if (FireMappingContext) Subsystem->AddMappingContext(FireMappingContext, 1);
		}

		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
		{
			// Get action mappings from weapon
			if (FireAction)
			{
				for (FEnhancedInputActionEventBinding& Binding : Bindings)
				{
					EnhancedInputComponent->RemoveBinding(Binding);
				}
			}
			FireAction = Weapon->GetFireAction();
			if (!FireAction) return;
			
			// Fire
			Bindings.Add(EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &UWeaponComponent::Fire));
			Bindings.Add(EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &UWeaponComponent::FireStarted));
			Bindings.Add(EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Completed, this, &UWeaponComponent::FireCompleted));
		}
	}
}

AWeapon* UWeaponComponent::GetWeapon()
{
	return Weapon;
}

void UWeaponComponent::Fire(const FInputActionValue& Value)
{
	Weapon->Fire(GetShootingDirection());
}

void UWeaponComponent::FireStarted(const FInputActionValue& Value)
{
	Weapon->FireStarted(GetShootingDirection());
}

void UWeaponComponent::FireCompleted(const FInputActionValue& Value)
{
	Weapon->FireCompleted(GetShootingDirection());
}

void UWeaponComponent::InitWithPlayer(AVoidCharacter* OwningPlayer)
{
	this->Player = OwningPlayer;
}

const FRotator& UWeaponComponent::GetShootingDirection()
{
	FRotator ShootDirection = FRotator::ZeroRotator;
	if (Player) ShootDirection = Player->GetFirstPersonCameraComponent()->GetComponentRotation();
	return ShootDirection;
}
