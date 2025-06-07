// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponCoreBase.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS(Blueprintable)
class VOID_API AWeapon : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWeapon();

	// ~~~ Weapon specific stats ~~~

	/** Amount of slots, this weapon occupies, calculated from all modifiers */
	UPROPERTY(BlueprintReadOnly, Category = "Weapon|Stats")
	uint8 WeaponSize;
	
	/** Damage per hit, calculated from all modifiers */
	UPROPERTY(BlueprintReadOnly, Category = "Weapon|Stats")
	float Damage;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<UWeaponCoreBase> WeaponCoreClass;

protected:

	UPROPERTY(BlueprintReadOnly)
	UWeaponCoreBase* WeaponCore;

	UPROPERTY(BlueprintReadOnly)
	TArray<UWeaponModuleBase*> WeaponModules;
	
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// ~~~ Weapon specific functions ~~~

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void Shoot();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void Reload();
	
};
