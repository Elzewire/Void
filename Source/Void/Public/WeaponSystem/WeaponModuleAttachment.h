// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponModuleData.h"
#include "UObject/Object.h"
#include "WeaponModuleAttachment.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, DefaultToInstanced, EditInlineNew)
class VOID_API UWeaponModuleAttachment : public UObject
{
	GENERATED_BODY()

public:
	UWeaponModuleAttachment();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Module Attachment")
	UWeaponModuleData* ModuleData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Module Attachment")
	FName AttachToSocket;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category = "Module Attachment")
	TArray<UWeaponModuleAttachment*> ChildAttachments;
};
