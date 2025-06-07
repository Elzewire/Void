// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponModuleSlot.h"
#include "Components/SceneComponent.h"
#include "WeaponCoreBase.generated.h"


UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class VOID_API UWeaponCoreBase : public USceneComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UWeaponCoreBase();

	// ~~~ Weapon Core common properties ~~~
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Weapon Core | Base")
	TSubclassOf<AActor> AmmunitionClass;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Weapon Core | Base")
	TArray<FWeaponModuleSlot> ModuleSlots;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon Core | Stats")
	uint8 Weight;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon Core | Stats")
	float Damage;
	
	// ~~~ Weapon Core common functions ~~~
	virtual void Shoot();
	virtual void Reload();
};
