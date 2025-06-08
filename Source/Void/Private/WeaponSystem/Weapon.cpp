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
	AttachModulesRecursive(WeaponCoreData, EquippedModuleAttachments, WeaponCoreMesh);
}

void AWeapon::AttachModulesRecursive(UWeaponPartData* ParentPartData, const TArray<UWeaponModuleAttachment*>& Attachments, USceneComponent* AttachToComponent)
{
	if (!ParentPartData || !AttachToComponent) return;

	for (UWeaponModuleAttachment* ModuleAttachment: Attachments)
	{
		if (!ModuleAttachment || !ModuleAttachment->ModuleData)
		{
			UE_LOG(LogBlueprint, Warning, TEXT("Module data asset not specified. Module will not be attached"))
			continue;
		}

		const FModuleSocket* ModuleSocket = ParentPartData->ModuleSockets.Find(ModuleAttachment->AttachToSocket);

		bool bIsModuleAllowed = false;
		if (ModuleSocket)
		{
			bIsModuleAllowed = ModuleAttachment->ModuleData->GetClass()->IsChildOf(ModuleSocket->AllowedModules); 
		}
		else
		{
			UE_LOG(LogBlueprint, Warning, TEXT("Socket '%s' not found on parent part '%s'. Module will not be attached."),
				*ModuleAttachment->AttachToSocket.ToString(), *ParentPartData->GetName());
			continue;
		}

		if (!bIsModuleAllowed)
		{
			UE_LOG(LogTemp, Warning, TEXT("Module '%s' is not allowed on socket '%s' of parent part '%s'. Skipping."),
				*ModuleAttachment->ModuleData->GetName(), *ModuleAttachment->AttachToSocket.ToString(), *ParentPartData->GetName());
			continue;
		}

		// Generate static mesh component for this module
		UStaticMeshComponent* ModuleMeshComponent = NewObject<UStaticMeshComponent>(this, NAME_None, RF_Transient);
		ModuleMeshComponent->SetStaticMesh(ModuleAttachment->ModuleData->ModuleMesh);
		ModuleMeshComponent->AttachToComponent(AttachToComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale, ModuleAttachment->AttachToSocket);
		ModuleMeshComponent->RegisterComponent();
		ModuleMeshes.Add(ModuleMeshComponent);
		
		if (ModuleAttachment->ChildAttachments.Num() > 0)
		{
			AttachModulesRecursive(ModuleAttachment->ModuleData, ModuleAttachment->ChildAttachments, ModuleMeshComponent);
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

