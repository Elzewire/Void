// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponSystem/ShootingStrategies/LaserShootingStrategy.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

#include "WeaponSystem/Weapon.h"

void ULaserShootingStrategy::Shoot(AWeapon* Weapon, const FVector& MuzzleLocation, const FRotator& ShootDirection)
{
	// TODO : Here we actually DEAL DAMAGE for all hit actors
}

void ULaserShootingStrategy::UpdateShootingEffects(float DeltaTime, AWeapon* Weapon, const FVector& MuzzleLocation, const FRotator& ShootDirection)
{
	Super::UpdateShootingEffects(DeltaTime, Weapon, MuzzleLocation, ShootDirection);
	
	if (!Weapon) return;
	HitActors.Empty();
	HitLocations.Empty();	
	HitLocations.Add(MuzzleLocation);

	ShootDir = ShootDirection;
	
	if (Weapon->WeaponStats.ShootingType == EShootingType::HOLD_FIRE)
	{
		FVector PrevLocation = MuzzleLocation;
		FRotator PrevDir = ShootDirection;
		
		for (int i = 0; i <= Weapon->WeaponStats.PiercingAmount; i++)
		{
			const float MaxRange = 10000.f;
			FCollisionQueryParams Params;
			Params.AddIgnoredActor(Weapon);
			Params.bTraceComplex = true;

			FHitResult HitResult;
			bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult,PrevLocation, PrevLocation + PrevDir.Vector() * MaxRange, ECC_Visibility, Params);

			if (!bHit)
			{
				HitLocations.Add(PrevLocation + PrevDir.Vector() * MaxRange);
				break;
			}
			HitLocations.Add(HitResult.Location);
			
			if (CanReflect(HitResult))
			{
				PrevLocation = HitResult.Location;
				PrevDir = CalcReflectionDir(HitResult, PrevDir);
				continue;
			}

			if (HitResult.GetActor())
			{
				PrevLocation = HitResult.Location;
				HitActors.Add(HitResult.GetActor());
				continue;
			}
			
			break;
		}
	}

	// Update laser effects
	for (UNiagaraComponent* Component : FX)
	{
		Component->SetVisibility(false);
	}
	
	for (int i = 0; i < HitLocations.Num() - 1; i++)
	{
		if (FX.IsValidIndex(i))
		{
			if (!FX[i]->IsVisible()) FX[i]->SetVisibility(true);
			FX[i]->SetWorldLocation(HitLocations[i]);
			FX[i]->SetVariableVec3(LaserEndParamName, HitLocations[i+1]);
		}
	}

	// Debug laser effects
	for (int i = 1; i < HitLocations.Num(); i++)
	{
		DrawDebugLine(GetWorld(), HitLocations[i-1], HitLocations[i], FColor::Green, false, -1, 0, 2);
	}
}

void ULaserShootingStrategy::SpawnShootingEffects(AWeapon* Weapon)
{
	Super::SpawnShootingEffects(Weapon);
	
	FX.Empty();
	
	if (!Weapon) return;
	
	for (int i = 0; i <= Weapon->WeaponStats.PiercingAmount; i++)
	{
		if (Weapon->WeaponStats.ProjectileEffect)
		{
			UNiagaraComponent* NiagaraComp = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Weapon->WeaponStats.ProjectileEffect, Weapon->GetActorLocation());
			NiagaraComp->SetVisibility(false);
			FX.Add(NiagaraComp);
		}
	}
}

void ULaserShootingStrategy::DestroyShootingEffects()
{
	Super::DestroyShootingEffects();

	for (UNiagaraComponent* Component : FX)
	{
		if (Component)
		{
			Component->Deactivate();
		}
	}
}

bool ULaserShootingStrategy::CanReflect(const FHitResult& HitResult) const
{
	if (HitResult.Component.IsValid()) return HitResult.Component->ComponentHasTag(ReflectiveTag);
	return false;
}

FRotator ULaserShootingStrategy::CalcReflectionDir(const FHitResult& HitResult, const FRotator& IncomingDir)
{
	return (IncomingDir.Vector() - 2.0f * FVector::DotProduct(HitResult.ImpactNormal, IncomingDir.Vector()) * HitResult.ImpactNormal).Rotation();
}


