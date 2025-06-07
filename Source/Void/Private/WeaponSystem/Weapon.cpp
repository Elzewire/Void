// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponSystem/Weapon.h"


// Sets default values
AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWeapon::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	if (!WeaponCoreClass) return;
	WeaponCore = NewObject<UWeaponCoreBase>(this, WeaponCoreClass);
	WeaponCore->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeapon::Shoot()
{
	
}

void AWeapon::Reload()
{
	
}

