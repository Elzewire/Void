// Fill out your copyright notice in the Description page of Project Settings.


#include "Void/Public/TimeDilationZone.h"

#include "DilatableInterface.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ATimeDilationZone::ATimeDilationZone()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATimeDilationZone::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATimeDilationZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Dilate time for other actors
	UpdateTimeDilation();
}

void ATimeDilationZone::UpdateTimeDilation()
{
	//UE_LOG(LogTemp, Warning, TEXT("Updating TD"))
	AActor* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (!Player) return;

	float PlayerDistance = FVector::Dist(GetActorLocation(), Player->GetActorLocation());

	// Get all actors
	TArray<AActor*> Actors;
	//UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UDilatableInterface::StaticClass(), Actors);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), Actors);

	for (AActor* Actor : Actors)
	{
		if (!Actor || Actor == Player) continue;

		float ActorDistance = FVector::Dist(GetActorLocation(), Actor->GetActorLocation());
		float NormalizedDistance = FMath::Clamp(ActorDistance / MaxRadius, 0.f, 1.f);

		// Slow down this actor if player is outside the zone
		if (PlayerDistance > MaxRadius)
		{
			float Dilation = FMath::Lerp(MinDilation, 1.0f, NormalizedDistance);
			Actor->CustomTimeDilation = Dilation;
		}
		// If player is inside the zone
		else
		{
			if (ActorDistance < MaxRadius)
			{
				if (ActorDistance > PlayerDistance)
				{
					// If this actor is further from center than player, speed up
					float PlayerNorm = FMath::Clamp((ActorDistance - PlayerDistance) / (MaxRadius - PlayerDistance), 0.f, 1.f);
					float Dilation = FMath::Lerp(1.0f, MaxDilation, PlayerNorm);
					Actor->CustomTimeDilation = Dilation;
				} else
				{
					// If this actor is closer to center than player, slow down
					float PlayerNorm = FMath::Clamp((PlayerDistance - ActorDistance) / PlayerDistance, 0.f, 1.f);
					float Dilation = FMath::Lerp(MinDilation, 1.0f, PlayerNorm);
					Actor->CustomTimeDilation = Dilation;
				}
			}
			else
			{
				Actor->CustomTimeDilation = MaxDilation;
			}
		}
	}
}
