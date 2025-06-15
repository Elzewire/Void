// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponSystem/WeaponShootingStrategy.h"
#include "LaserShootingStrategy.generated.h"

class UNiagaraComponent;
/**
 * 
 */
UCLASS(Blueprintable)
class VOID_API ULaserShootingStrategy : public UWeaponShootingStrategy
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Laser Shooting")
	virtual void Shoot(AWeapon* Weapon, const FVector& MuzzleLocation, const FRotator& ShootDirection) override;
	
	UFUNCTION(BlueprintCallable, Category = "Laser Shooting")
	virtual void UpdateShootingEffects(float DeltaTime, AWeapon* Weapon, const FVector& MuzzleLocation, const FRotator& ShootDirection) override;

	UFUNCTION(BlueprintCallable, Category = "Laser Shooting")
	virtual void SpawnShootingEffects(AWeapon* Weapon) override;
	
	UFUNCTION(BlueprintCallable, Category = "Laser Shooting")
	virtual void DestroyShootingEffects() override;
	
protected:
	/** Tag name on surfaces, that can reflect laser */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Laser Shooting")
	FName ReflectiveTag;
	
	/** Name of a beam end parameter on laser niagara FX*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Laser Shooting")
	FName LaserEndParamName;
	
	UPROPERTY(BlueprintReadOnly)
	TArray<AActor*> HitActors;

	UPROPERTY(BlueprintReadOnly)
	TArray<FVector> HitLocations;
	
	UPROPERTY(BlueprintReadOnly)
	FRotator ShootDir;

	UPROPERTY()
	TArray<UNiagaraComponent*> FX;
	
	bool CanReflect(const FHitResult& HitResult) const;
	FRotator CalcReflectionDir(const FHitResult& HitResult, const FRotator& IncomingDir);
};
