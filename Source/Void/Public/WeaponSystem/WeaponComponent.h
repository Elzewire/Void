// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "WeaponComponent.generated.h"

UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class VOID_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	USoundBase* FireSound;
	
	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* FireAnimation;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	FVector MuzzleOffset;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* FireMappingContext;

	/** Fire Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* FireAction;

	/** Socket on player mesh to attach to */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Weapon")
	FName WeaponSocket;
	
	/** Sets default values for this component's properties */
	UWeaponComponent();
	
	UFUNCTION(BlueprintCallable, Category="Weapon")
	void AttachWeapon(AWeapon* Weapon);

	UFUNCTION(BlueprintCallable, Category="Weapon")
	AWeapon* GetWeapon();
	
	/** Start shooting (hold) */
	UFUNCTION(BlueprintCallable, Category="Weapon")
	void ShootStart();
	
	/** Stop shooting */
	UFUNCTION(BlueprintCallable, Category="Weapon")
	void ShootEnd();
	
	UFUNCTION(BlueprintCallable, Category="Weapon Component")
	void InitWithPlayer(AVoidCharacter* OwningPlayer);

protected:
	// TODO : Change to array or map of weapons, to hold multiple
	UPROPERTY(BlueprintReadOnly, Category = "Weapon")
	AWeapon* Weapon;

	UPROPERTY()
	FTimerHandle ShootingTimer;
	
	UPROPERTY()
	float LastTime;

	/** Fire a single shot */
	UFUNCTION(BlueprintCallable, Category="Weapon")
	void Shoot();

	/** Update our weapon with player's current aim direction */
	UFUNCTION(BlueprintCallable, Category="Weapon")
	void UpdateAimDirection();
	
	UPROPERTY(BlueprintReadOnly)
	AVoidCharacter* Player;
};
