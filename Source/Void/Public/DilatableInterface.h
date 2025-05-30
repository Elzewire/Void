// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DilatableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UDilatableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class VOID_API IDilatableInterface
{
	GENERATED_BODY()

public:
	virtual void SetTimeDilation(float NewTimeDilation);
};
