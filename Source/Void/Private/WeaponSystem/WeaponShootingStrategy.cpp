// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponSystem\WeaponShootingStrategy.h"

void UWeaponShootingStrategy::InitWithWeapon(AWeapon* InitWeapon)
{
	Weapon = InitWeapon;
}

void UWeaponShootingStrategy::Shoot(const FRotator& ShootDirection)
{
}

void UWeaponShootingStrategy::OnFireStart(const FRotator& ShootDirection)
{
}

void UWeaponShootingStrategy::OnFire(const FRotator& ShootDirection)
{
}

void UWeaponShootingStrategy::OnFireStop(const FRotator& ShootDirection)
{
}

void UWeaponShootingStrategy::UpdateShootingEffects(const FRotator& ShootDirection)
{
}

void UWeaponShootingStrategy::SpawnShootingEffects()
{
}

void UWeaponShootingStrategy::DestroyShootingEffects()
{
}
