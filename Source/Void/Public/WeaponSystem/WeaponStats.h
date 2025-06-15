#pragma once

#include "WeaponStats.generated.h"

class UNiagaraSystem;
class AVoidProjectileBase;

UENUM(BlueprintType)
enum class EDamageType : uint8
{
	KINETIC = 0 UMETA(DisplayName = "Kinetic"),
	ENERGETIC = 1 UMETA(DisplayName = "Energetic"),
	SPECIAL = 2 UMETA(DisplayName = "Special")
};

UENUM(BlueprintType)
enum class EWeaponSize : uint8
{
	LIGHT = 0 UMETA(DisplayName = "Light"), // Size <= 10
	MEDIUM = 1 UMETA(DisplayName = "Medium"), // Size <= 20
	HEAVY = 2 UMETA(DisplayName = "Heavy") // Size > 20
};

UENUM(BlueprintType)
enum class EShootingType : uint8
{
	SINGLE = 0 UMETA(DisplayName = "Single"), // Shoot after every click
	HOLD_FIRE = 1 UMETA(DisplayName = "Hold To Fire"), // Single + holding to fire automatically
	HOLD_BURST = 2 UMETA(DisplayName = "Hold To Burst"), // Sinlge + holding to fire a powerful shot
};

USTRUCT(BlueprintType)
struct FWeaponStats
{
	GENERATED_USTRUCT_BODY()
	// TODO : Some properties can be repositioned
	// List of all weapon stats, including the ones that are not used in some weapons

	// ~~~ General
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon stats")
	EShootingType ShootingType;
	
	/** Weapon damage modifier */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon stats")
	float Damage;

	/** Weapon damage type */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon stats")
	EDamageType DamageType;

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
	float PiercingMultiplier;
	
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visuals")
	UNiagaraSystem* MuzzleFlashEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visuals")
	UNiagaraSystem* ProjectileEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visuals")
	UNiagaraSystem* HitEffect;
};
