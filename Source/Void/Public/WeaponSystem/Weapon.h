// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TP_PickUpComponent.h"
#include "WeaponShootingStrategy.h"
#include "GameFramework/Actor.h"
#include "WeaponSystem/WeaponModuleAttachment.h"
#include "Weapon.generated.h"

class UFireMode;
enum class ETriggerEvent : uint8;
class UWeaponPartData;
class UWeaponModuleData;
class UWeaponCoreData;
class AVoidCharacter;

UCLASS(Blueprintable)
class VOID_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AWeapon();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	UTP_PickUpComponent* PickUpComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Component")
	USceneComponent* MuzzleComponent;
	
	// ~~~ BEGIN Weapon specific stats ~~~
    UPROPERTY(BlueprintReadOnly, Category = "Weapon|Stats")
	FWeaponStats WeaponStats;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Composition")
	UWeaponCoreData* WeaponCoreData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced, Category = "Weapon|Composition")
	TArray<UWeaponModuleAttachment*> EquippedModuleAttachments;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Composition")
	FName MuzzleSocketName;
	// ~~~ END Weapon specific stats ~~~

	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// ~~~ BEGIN Weapon specific functions ~~~
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void FireStarted(const FRotator& ShootDirection);
	
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void Fire(const FRotator& ShootDirection);
	
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void FireCompleted(const FRotator& ShootDirection);

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void Reload();
	
	UFUNCTION(BlueprintCallable, Category = "Weapon|Fire Mode")
	UInputAction* GetFireAction();

	UFUNCTION(BlueprintCallable, Category = "Weapon|Fire Mode")
	UInputMappingContext* GetFireMappingContext();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FTransform GetMuzzleTransform();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	USceneComponent* GetMuzzleComponent();
	// ~~~ END Weapon specific functions ~~~
	
protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components")
	USkeletalMeshComponent* WeaponCoreMesh;
	
	UPROPERTY(Transient)
	TArray<UStaticMeshComponent*> ModuleMeshes;

	UPROPERTY(BlueprintReadOnly)
	UWeaponShootingStrategy* ShootingStrategy;

	UPROPERTY(BlueprintReadOnly)
	UFireMode* FireMode;
	
	UPROPERTY(BlueprintReadOnly)
	FRotator AimDirection;
	
	UPROPERTY(BlueprintReadOnly)
	bool bIsShooting;
	
	UFUNCTION()
	void AttachModulesRecursive(UWeaponPartData* ParentPartData, const TArray<UWeaponModuleAttachment*>& Attachments, USceneComponent* AttachToComponent);

	UFUNCTION(BlueprintCallable)
	void AttachToPlayer(AVoidCharacter* Player);

	UFUNCTION(BlueprintCallable)
	void ConstructWeapon();
};
