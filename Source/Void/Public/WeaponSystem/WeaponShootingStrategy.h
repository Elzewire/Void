// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "WeaponShootingStrategy.generated.h"

class AWeapon;
/**
 * 
 */
UCLASS(Abstract)
class VOID_API UWeaponShootingStrategy : public UObject
{
	GENERATED_BODY()

public:
	virtual void Shoot(AWeapon* Weapon, const FVector& MuzzleLocation, const FRotator& MuzzleRotation);
};
