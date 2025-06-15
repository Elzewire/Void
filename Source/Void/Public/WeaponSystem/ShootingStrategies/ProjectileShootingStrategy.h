// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VoidProjectileBase.h"
#include "WeaponSystem/WeaponShootingStrategy.h"
#include "ProjectileShootingStrategy.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class VOID_API UProjectileShootingStrategy : public UWeaponShootingStrategy
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Projectile Shooting")
	virtual void Shoot(AWeapon* Weapon, const FVector& MuzzleLocation, const FRotator& ShootDirection) override;
};
