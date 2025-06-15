// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponSystem/ShootingStrategies/ProjectileShootingStrategy.h"
#include "WeaponSystem/Weapon.h"

void UProjectileShootingStrategy::Shoot(AWeapon* Weapon, const FVector& MuzzleLocation, const FRotator& ShootDirection)
{
	if (!Weapon) return;
	
	if (!Weapon->WeaponStats.ProjectileClass)
	{
		UE_LOG(LogBlueprint, Error, TEXT("Projectle class not specified!"));
		return;
	}
	
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = Weapon;
	SpawnParameters.Instigator = Weapon->GetInstigator();
	
	AVoidProjectileBase* Projectile = GetWorld()->SpawnActor<AVoidProjectileBase>(Weapon->WeaponStats.ProjectileClass, MuzzleLocation, ShootDirection, SpawnParameters);
	// TODO: Here we can add some projectile modifications from weapon
}