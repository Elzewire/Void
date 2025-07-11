// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "WeaponStatModifier.generated.h"

struct FWeaponStats;

/**
 * 
 */
UCLASS(Abstract)
class VOID_API UWeaponStatModifier : public UObject
{
	GENERATED_BODY()

public:
	virtual void ApplyModifier(FWeaponStats& Stats);
	
protected:
	/** Higher priority modifiers applied first */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Stat Modifier")
	int Priority;

	friend bool operator<(const UWeaponStatModifier& Lhs, const UWeaponStatModifier& RHS)
	{
		// Reversed, to use with TArray sort, descending
		return Lhs.Priority > RHS.Priority;
	}
};
