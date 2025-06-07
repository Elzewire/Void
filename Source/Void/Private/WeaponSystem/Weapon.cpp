// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponSystem/Weapon.h"

#include "Interfaces/IPluginManager.h"
#include "WeaponSystem/WeaponCoreData.h"
#include "WeaponSystem/WeaponModuleData.h"


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

	// Destroy previously created mesh components
	for (auto Mesh : ModuleMeshes)
	{
		Mesh->UnregisterComponent();
		Mesh->DestroyComponent();
	}

	ModuleMeshes.Empty();
	
	// Check for core component
	if (!WeaponCoreData)
	{
		UE_LOG(LogBlueprint, Warning, TEXT("Weapon core not specified"))
		return;
	}

	// Destroy mesh
	if (WeaponCoreMesh)
	{
		WeaponCoreMesh->UnregisterComponent();
		WeaponCoreMesh->DestroyComponent();
	}
	
	// Add CoreMesh to the scene
	WeaponCoreMesh = NewObject<USkeletalMeshComponent>(this, NAME_None, RF_Transient);
	WeaponCoreMesh->SetSkeletalMeshAsset(WeaponCoreData->CoreMesh);
	WeaponCoreMesh->RegisterComponent();
	WeaponCoreMesh->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	// Create shooting strategy
	if (!WeaponCoreData->ShootingStrategyClass)
	{
		UE_LOG(LogBlueprint, Warning, TEXT("Shooting strategy not specified for this core"))
		return;
	}

	// TODO : Consider destroying previous object
	ShootingStrategy = NewObject<UWeaponShootingStrategy>(this, WeaponCoreData->ShootingStrategyClass);
	
	// Reassemble modules
	AttachModulesRecursive(WeaponCoreData, EquippedModules, WeaponCoreMesh);
}

void AWeapon::AttachModulesRecursive(UWeaponPartData* ParentPartData, const TArray<FEquippedModuleData>& ModulesToAttach, USceneComponent* AttachToComponent)
{
	if (!ParentPartData || !AttachToComponent) return;

	for (const FEquippedModuleData& EquippedModule: ModulesToAttach)
	{
		if (!EquippedModule.ModuleDataAsset)
		{
			UE_LOG(LogBlueprint, Warning, TEXT("Module data asset not specified. Module will not be attached"))
			continue;
		}

		const FModuleSocket* ModuleSocket = ParentPartData->ModuleSockets.Find(EquippedModule.AttachToSocket);

		bool bIsModuleAllowed = false;
		if (ModuleSocket)
		{
			bIsModuleAllowed = EquippedModule.ModuleDataAsset->GetClass()->IsChildOf(ModuleSocket->AllowedModules); 
		}
		else
		{
			UE_LOG(LogBlueprint, Warning, TEXT("Socket '%s' not found on parent part '%s'. Module will not be attached."),
				*EquippedModule.AttachToSocket.ToString(), *ParentPartData->GetName());
			continue;
		}

		if (!bIsModuleAllowed)
		{
			UE_LOG(LogTemp, Warning, TEXT("Module '%s' is not allowed on socket '%s' of parent part '%s'. Skipping."),
				*EquippedModule.ModuleDataAsset->GetName(), *EquippedModule.AttachToSocket.ToString(), *ParentPartData->GetName());
			continue;
		}

		// Generate static mesh component for this module
		UStaticMeshComponent* ModuleMeshComponent = NewObject<UStaticMeshComponent>(this, NAME_None, RF_Transient);
		ModuleMeshComponent->SetStaticMesh(EquippedModule.ModuleDataAsset->ModuleMesh);
		ModuleMeshComponent->AttachToComponent(AttachToComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale, EquippedModule.AttachToSocket);
		ModuleMeshComponent->RegisterComponent();
		ModuleMeshes.Add(ModuleMeshComponent);
		
		if (EquippedModule.ChildModules.Num() > 0)
		{
			AttachModulesRecursive(EquippedModule.ModuleDataAsset, EquippedModule.ChildModules, ModuleMeshComponent);
		}
	}
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeapon::Shoot()
{
	if (!ShootingStrategy) return;
	// TODO : Should calculate muzzle location dynamically (using the modules)
	ShootingStrategy->Shoot(this, GetActorLocation(), GetActorRotation());
}

void AWeapon::Reload()
{
	
}

