// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponSystem/ShootingStrategies/LaserShootingStrategy.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

#include "WeaponSystem/Weapon.h"

ULaserShootingStrategy::ULaserShootingStrategy()
{
	ReflectiveTag = TEXT("Reflective");
	LaserEndParamName = TEXT("BeamEnd");
	ImpulseDuration = 1.0f;
	LastFireTime = 0;
	bFXInitialized = false;
}

void ULaserShootingStrategy::OnFireStart(const FRotator& ShootDirection)
{
	Super::OnFireStart(ShootDirection);
	if (!bFXInitialized) InitializeFX();
}

/**
 * This function is called:
 * - once						 - on Single and Charged fire modes
 * - multiple times (on timer)	 - on Burst fire mode and
 * - every tick					 - on Continuous fire mode.
 */
void ULaserShootingStrategy::OnFire(const FRotator& ShootDirection)
{
	Super::OnFire(ShootDirection);
	
	TArray<FVector> HitLocations;
	TArray<AActor*> HitActors;
	TraceLaser(ShootDirection, HitLocations, HitActors);
	
	if (GetWorld()->GetTimeSeconds() - LastFireTime >= Weapon->WeaponStats.ShootingSpeed)
	{
		for (AActor * Hit : HitActors)
		{
			// TODO : Deal damage
		}
		LastFireTime = GetWorld()->GetTimeSeconds();
	}
	
	// Start from muzzle location for debug
	HitLocations.Insert(Weapon->GetMuzzleTransform().GetLocation(), 0);
	DebugTraceLaser(HitLocations);

	// Cosmetic effects
	UpdateFX(HitLocations);
}

void ULaserShootingStrategy::OnFireStop(const FRotator& ShootDirection)
{
	Super::OnFireStop(ShootDirection);

	// Wait a bit before destroying laser
	GetWorld()->GetTimerManager().SetTimer(ImpulseTimer, this, &ULaserShootingStrategy::DestroyFX, ImpulseDuration, false, ImpulseDuration);
}


void ULaserShootingStrategy::TraceLaser(const FRotator& ShootDirection, TArray<FVector>& HitLocations, TArray<AActor*>& HitActors)
{
	if (!Weapon) return;
	
	// Reset locations for laser beam
	HitActors.Empty();
	HitLocations.Empty();

	FRotator ShootDir = ShootDirection;

	FVector PrevLocation = Weapon->GetMuzzleTransform().GetLocation();
	FRotator PrevDir = ShootDirection;

	for (int i = 0; i <= Weapon->WeaponStats.PiercingAmount; i++)
	{
		const float MaxRange = 10000; // TODO : Magic number
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(Weapon);
		Params.bTraceComplex = true;

		FHitResult HitResult;
		bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, PrevLocation, PrevLocation + PrevDir.Vector() * MaxRange, ECC_Visibility, Params);
		if (!bHit)
		{
			// No hits, stop firing
			HitLocations.Add(PrevLocation + PrevDir.Vector() * MaxRange);
			break;
		}
		
		HitLocations.Add(HitResult.Location);

		if (CanReflect(HitResult))
		{
			// Reflective wall? Keep going
			PrevLocation = HitResult.Location;
			PrevDir = CalcReflectionDir(HitResult, PrevDir);
			continue;
		}

		if (HitResult.GetActor())
		{
			// Actor? Save and keep going
			PrevLocation = HitResult.Location;
			HitActors.Add(HitResult.GetActor());
			continue;
		}

		// Hit something else, stop
		break;
	}
}

void ULaserShootingStrategy::InitializeFX()
{
	FX.Empty();
	
	if (!Weapon) return;

	// Spawn FX
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

void ULaserShootingStrategy::UpdateFX(const TArray<FVector>& HitLocations)
{
	if (!Weapon) return;
	
	// Update laser effects
	for (UNiagaraComponent* Component : FX)
	{
		Component->SetVisibility(false);
	}
	
	for (int i = 0; i < HitLocations.Num(); i++)
	{
		if (FX.IsValidIndex(i))
		{
			if (!FX[i]->IsVisible()) FX[i]->SetVisibility(true);
			if (i == 0)
			{
				// Attach to weapon muzzle
				FX[i]->AttachToComponent(Weapon->GetMuzzleComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
				FX[i]->SetVariableVec3(LaserEndParamName, HitLocations[i]);
				continue;
			}
			FX[i]->SetWorldLocation(HitLocations[i-1]);
			FX[i]->SetVariableVec3(LaserEndParamName, HitLocations[i]);
		}
	}
}

void ULaserShootingStrategy::DestroyFX()
{
	Super::DestroyShootingEffects();

	if (!Weapon) return;
	
	// Stop drawing laser beam after we stopped shooting
	for (UNiagaraComponent* Component : FX)
	{
		if (Component)
		{
			Component->Deactivate();
		}
	}
}

void ULaserShootingStrategy::DebugTraceLaser(const TArray<FVector>& HitLocations)
{
	// Debug laser effects
	for (int i = 1; i < HitLocations.Num(); i++)
	{
		DrawDebugLine(GetWorld(), HitLocations[i-1], HitLocations[i], FColor::Green, false, -1, 0, 2);
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



