// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponSystem/WeaponCoreBase.h"
#include "BeamWeaponCoreBase.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class VOID_API UBeamWeaponCoreBase : public UWeaponCoreBase
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UBeamWeaponCoreBase();
	
};
