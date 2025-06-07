#pragma once
#include "WeaponModuleSlot.generated.h"

class UWeaponModuleBase;

USTRUCT(BlueprintType)
struct FWeaponModuleSlot
{
	GENERATED_USTRUCT_BODY();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName SocketName;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<TSubclassOf<UWeaponModuleBase>> AllowedModuleClasses;

	UPROPERTY(BlueprintReadOnly)
	UWeaponModuleBase* InstalledModule;
};
