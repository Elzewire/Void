// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponShootingStrategy.h"
#include "GameFramework/Actor.h"
#include "WeaponSystem/WeaponModuleAttachment.h"
#include "Weapon.generated.h"

class UWeaponPartData;
class UWeaponModuleData;
class UWeaponCoreData;

UCLASS(Blueprintable)
class VOID_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AWeapon();

	// ~~~ Weapon specific stats ~~~

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon | Composition")
	UWeaponCoreData* WeaponCoreData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced, Category = "Weapon | Composition")
	TArray<UWeaponModuleAttachment*> EquippedModuleAttachments;
	
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// ~~~ Weapon specific functions ~~~

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void Shoot();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void Reload();
	
protected:

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components")
	USkeletalMeshComponent* WeaponCoreMesh;
	
	UPROPERTY(Transient)
	TArray<UStaticMeshComponent*> ModuleMeshes;

	UPROPERTY(BlueprintReadOnly)
	UWeaponShootingStrategy* ShootingStrategy;

	UFUNCTION()
	void AttachModulesRecursive(UWeaponPartData* ParentPartData, const TArray<UWeaponModuleAttachment*>& Attachments, USceneComponent* AttachToComponent);
};
