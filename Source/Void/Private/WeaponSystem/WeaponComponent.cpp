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
			EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &UWeaponComponent::ShootStart);
			EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Ongoing, this, &UWeaponComponent::UpdateAimDirection);
			EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Completed, this, &UWeaponComponent::ShootEnd);
		}
	}
}

AWeapon* UWeaponComponent::GetWeapon()
{
	return Weapon;
}

void UWeaponComponent::ShootStart()
{
	if (Weapon)
	{
		Weapon->StartShootingEffects();

		// Time since last shot
		const float Delay = FMath::Clamp(Weapon->WeaponStats.ShootingSpeed - (GetWorld()->GetTimeSeconds() - LastTime), 0.0f, Weapon->WeaponStats.ShootingSpeed);

		GetWorld()->GetTimerManager().SetTimer(ShootingTimer, this, &UWeaponComponent::Shoot, Weapon->WeaponStats.ShootingSpeed, true, Delay);
	}
}

void UWeaponComponent::Shoot()
{
	if (!Player) return;
	FRotator ShootDirection = Player->GetFirstPersonCameraComponent()->GetComponentRotation();
	
	if (Weapon) Weapon->Shoot(ShootDirection);
	LastTime = GetWorld()->GetTimeSeconds();
}

void UWeaponComponent::ShootEnd()
{
	if (Weapon) Weapon->EndShootingEffects();
	GetWorld()->GetTimerManager().ClearTimer(ShootingTimer);
}

void UWeaponComponent::UpdateAimDirection()
{
	UE_LOG(LogTemp, Warning, TEXT("ONGOING"))
	if (!Player) return;
	const FRotator ShootDirection = Player->GetFirstPersonCameraComponent()->GetComponentRotation();
	
	if (Weapon) Weapon->UpdateAimDirection(ShootDirection);
}

void UWeaponComponent::InitWithPlayer(AVoidCharacter* OwningPlayer)
{
	this->Player = OwningPlayer;
}