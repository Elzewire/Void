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
	ULaserShootingStrategy();

	UFUNCTION(BlueprintCallable, Category = "Laser Shooting")
	virtual void OnFireStart(const FRotator& ShootDirection) override;
	
	UFUNCTION(BlueprintCallable, Category = "Laser Shooting")
	virtual void OnFire(const FRotator& ShootDirection) override;
	
	UFUNCTION(BlueprintCallable, Category = "Laser Shooting")
	virtual void OnFireStop(const FRotator& ShootDirection) override;
	
	UFUNCTION(BlueprintCallable, Category = "Laser Shooting")
	virtual void TraceLaser(const FRotator& ShootDirection, TArray<FVector>& HitLocations, TArray<AActor*>& HitActors);

	UFUNCTION(BlueprintCallable, Category = "Laser Shooting|FX")
	void InitializeFX();
	
	UFUNCTION(BlueprintCallable, Category = "Laser Shooting|FX")
	void UpdateFX(const TArray<FVector>& HitLocations);

	UFUNCTION(BlueprintCallable, Category = "Laser Shooting|FX")
	void DestroyFX();
	
protected:
	/** Tag name on surfaces, that can reflect laser */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Laser Shooting")
	FName ReflectiveTag;
	
	/** Name of a beam end parameter on laser niagara FX*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Laser Shooting")
	FName LaserEndParamName;

	/** How long will laser live after burst shot in seconds */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Laser Shooting")
	float ImpulseDuration;

	UPROPERTY()
	float LastFireTime;

	UPROPERTY()
	FTimerHandle ImpulseTimer;
	
	UPROPERTY()
	TArray<UNiagaraComponent*> FX;
	
	bool bFXInitialized;
	bool CanReflect(const FHitResult& HitResult) const;
	FRotator CalcReflectionDir(const FHitResult& HitResult, const FRotator& IncomingDir);
	void DebugTraceLaser(const TArray<FVector>& HitLocations);
};
