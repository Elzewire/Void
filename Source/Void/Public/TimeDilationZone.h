// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimeDilationZone.generated.h"

UCLASS()
class VOID_API ATimeDilationZone : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATimeDilationZone();

protected:
	/** Sphere collision for zone */
	UPROPERTY(VisibleDefaultsOnly, Category = TimeDilationZone)
	USphereComponent* ZoneSphere;

	/** Dilation parameters */
	UPROPERTY(EditDefaultsOnly, Category = TimeDilationZone)
	float MaxDilation = 0.2f;
	UPROPERTY(EditDefaultsOnly, Category = TimeDilationZone)
	float MinDilation = 2.0f;
	UPROPERTY(EditDefaultsOnly, Category = TimeDilationZone)
	float MaxRadius = 2000.0f;

	UPROPERTY(BlueprintReadOnly)
	TSet<AActor*> OverlappingActors;
	UPROPERTY(BlueprintReadOnly)
	AActor* Player;
	UPROPERTY(BlueprintReadOnly)
	bool bIsplayerInside;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                  int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	void OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void UpdateTimeDilation();
};
