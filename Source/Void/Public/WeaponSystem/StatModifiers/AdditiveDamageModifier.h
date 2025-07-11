// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponSystem/WeaponStatModifier.h"
#include "WeaponSystem/WeaponStats.h"
#include "AdditiveDamageModifier.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class VOID_API UAdditiveDamageModifier : public UWeaponStatModifier
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Damage Modifier")
	virtual void ApplyModifier(FWeaponStats& Stats) override
	{
		Stats.Damage += this->Damage;
	};

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage Modifier")
	float Damage;
};
