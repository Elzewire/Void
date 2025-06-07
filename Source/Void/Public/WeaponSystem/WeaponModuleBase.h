// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponModuleSlot.h"
#include "Components/SceneComponent.h"
#include "WeaponModuleBase.generated.h"

UCLASS(Blueprintable, meta=(BlueprintSpawnableComponent))
class VOID_API UWeaponModuleBase : public USceneComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UWeaponModuleBase();

	// ~~~ Module Base common attributes ~~~
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Module")
	UStaticMesh* ModuleMesh;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Module")
	TArray<FWeaponModuleSlot> SubModuleSlots;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;	

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
