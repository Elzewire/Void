// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "WeaponPartData.generated.h"

/**
 * 
 */

class UWeaponModuleData;

USTRUCT(BlueprintType)
struct FModuleSocket
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	FName SocketName;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UWeaponModuleData> AllowedModules;
	
};

UCLASS()
class VOID_API UWeaponPartData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon Part")
	TMap<FName, FModuleSocket> ModuleSockets;
};
