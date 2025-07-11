// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponPartData.h"
#include "WeaponStats.h"
#include "WeaponCoreData.generated.h"

class UFireMode;
class UWeaponShootingStrategy;
class AAmmunition;
/**
 * 
 */
UCLASS()
class VOID_API UWeaponCoreData : public UWeaponPartData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon Core")
	USkeletalMesh* CoreMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Core")
	FWeaponStats DefaultStats;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon Core")
	TSubclassOf<AAmmunition> Ammunition;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon Core")
	TSubclassOf<UWeaponShootingStrategy> ShootingStrategyClass;
};
