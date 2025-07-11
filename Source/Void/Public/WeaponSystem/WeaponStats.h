#pragma once

#include "WeaponStats.generated.h"

class UNiagaraSystem;
class UInputMappingContext;
class UInputAction;
class AVoidProjectileBase;

UENUM(BlueprintType)
enum EDamageType : uint8
{
	DT_KINETIC = 0 UMETA(DisplayName = "Kinetic"),
	DT_ENERGETIC = 1 UMETA(DisplayName = "Energetic"),
	DT_SPECIAL = 2 UMETA(DisplayName = "Special"),
	DT_EMOTIONAL = 3 UMETA(DisplayName = "Special")
};

UENUM(BlueprintType)
enum EWeaponSize : uint8
{
	WS_LIGHT = 0 UMETA(DisplayName = "Light"), // Size <= 10
	WS_MEDIUM = 1 UMETA(DisplayName = "Medium"), // Size <= 20
	WS_HEAVY = 2 UMETA(DisplayName = "Heavy") // Size > 20
};

USTRUCT(BlueprintType)
struct FWeaponStats
{
	GENERATED_USTRUCT_BODY()
	// List of all weapon stats, including the ones that are not used in some weapons

	// ~~~ General
	/** Weapon damage modifier */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon stats")
	float Damage;

	/** Weapon damage type */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon stats")
	TEnumAsByte<EDamageType> DamageType;

	/** Max range after kinetic projectile starts falling, energetic weapons start losing their damage */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon stats")
	float Range;

	/** Scope zoom scale */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon stats")
	int Zoom;

	/** Size of a single ammo cartridge */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon stats")
	int AmmoSize;

	/** How much ammo single shot or beam hit eats */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon stats")
	int AmmoPerShot;

	/** Time delay between shots or beam hits */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon stats")
	float ShootingSpeed;

	/** Recoil angle per shot or beam hit */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon stats")
	float Recoil;
	
	/** Max horizontal dispersion angle from straight shooting direction */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon stats")
	float HorDispersion;

	/** Max vertical dispersion angle from straight shooting direction */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon stats")
	float VerDispersion;

	/** Size this weapon part */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon stats")
	int Size;
	
	/** How many enemies can a single projectile penetrate
	 * How many laser reflections are possible
	 * How many enemies a single arc beam jumps to */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon stats")
	int PiercingAmount;

	/** Damage reduction for every pierced enemy (only if piercing > 0) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon stats")
	float PiercingMultiplier;

	/** For different fire modes */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon stats")
	UInputMappingContext* FireMappingContext;

	/** For different fire modes */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon stats")
	UInputAction* FireInputAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon stats")
	
	// ~~~ Projectile only
	/** What type of projectile to spawn */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projectile weapon stats")
	TSubclassOf<AVoidProjectileBase> ProjectileClass;
	
	/** How many projectiles are spawned per shot */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile weapon stats")
	int ProjectilesPerShot;

	/** Initial speed of a projectile */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile weapon stats")
	float ProjectileSpeed;

	// ~~~ Visuals
	/** Spawned at weapon muzzle when firing */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visuals")
	UNiagaraSystem* MuzzleFlashEffect;

	/** Spawned when firing or delegated to a projectile */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visuals")
	UNiagaraSystem* ProjectileEffect;

	/** Spawned when enemy or surface is hit or delegated to a projectile */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visuals")
	UNiagaraSystem* HitEffect;
};
