// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimeDilationZone.generated.h"

UCLASS(Blueprintable)
class VOID_API ATimeDilationZone : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATimeDilationZone();

protected:
	/** Dilation parameters */
	UPROPERTY(BlueprintReadWrite, Category = TimeDilationZone)
	float MaxDilation = 2.0f;
	UPROPERTY(BlueprintReadWrite, Category = TimeDilationZone)
	float MinDilation = 0.2f;
	UPROPERTY(BlueprintReadWrite, Category = TimeDilationZone)
	float MaxRadius = 2000.0f;

	UPROPERTY(BlueprintReadOnly)
	TSet<AActor*> OverlappingActors;
	UPROPERTY(BlueprintReadOnly)
	bool bIsplayerInside;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void UpdateTimeDilation();
};
