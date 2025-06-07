// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VoidProjectile.h"
#include "WeaponSystem/WeaponCoreBase.h"
#include "ProjectileWeaponCoreBase.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class VOID_API UProjectileWeaponCoreBase : public UWeaponCoreBase
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UProjectileWeaponCoreBase();

	// ~~~ Projectile Weapon Core common properties ~~~
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Weapon Core | Projectile")
	TSubclassOf<AVoidProjectile> ProjectileClass;
};
