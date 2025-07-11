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

	UFUNCTION(BlueprintCallable, Category = "Shooting strategy")
	void InitWithWeapon(AWeapon* InitWeapon);
	
	virtual void OnFireStart(const FRotator& ShootDirection);
	virtual void OnFire(const FRotator& ShootDirection);
	virtual void OnFireStop(const FRotator& ShootDirection);
protected:
	UPROPERTY(BlueprintReadOnly)
	AWeapon* Weapon;
};
