// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponPartData.h"
#include "WeaponModuleData.generated.h"

class UWeaponStatModifier;

/**
 * 
 */
UCLASS()
class VOID_API UWeaponModuleData : public UWeaponPartData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon Module")
	UStaticMesh* ModuleMesh;

	UPROPERTY(EditAnywhere, Instanced, BlueprintReadWrite, Category = "Modifiers")
	TArray<UWeaponStatModifier*> Modifiers;
};
