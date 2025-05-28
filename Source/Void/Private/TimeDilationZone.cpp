// Fill out your copyright notice in the Description page of Project Settings.


#include "Void/Public/TimeDilationZone.h"

#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ATimeDilationZone::ATimeDilationZone()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Zone->OnComponentBeginOverlap.AddDynamic(this, &ATimeDilationZone::OverlapBegin);
}

// Called when the game starts or when spawned
void ATimeDilationZone::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATimeDilationZone::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor) return;
	Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (OtherActor == Player)
	{
		bIsplayerInside = true;
		return;
	}
	OverlappingActors.Add(OtherActor);
}

void ATimeDilationZone::OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor) return;
	if (Player && OtherActor == Player)
	{
		Player = nullptr;
		bIsplayerInside = false;
		return;
	}
	OverlappingActors.Remove(OtherActor);
}

// Called every frame
void ATimeDilationZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Dilate time for other actors
	//UpdateTimeDilation();
}

void ATimeDilationZone::UpdateTimeDilation()
{
	UE_LOG(LogTemp, Warning, TEXT("Updating TD"))
	AActor* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (!Player) return;

	FVector ZoneCenter = GetActorLocation();
	FVector PlayerLocation = Player->GetActorLocation();
	float PlayerDistance = FVector::Dist(ZoneCenter, PlayerLocation);

	// Get all actors
	TArray<AActor*> Actors;
	ZoneSphere->GetOverlappingActors(OverlappingActors, ACharacter::StaticClass());

	for (AActor* Actor : OverlappingActors)
	{
		if (!Actor || Actor == Player) continue;

		float ActorDistance = FVector::Dist(ZoneCenter, Actor->GetActorLocation());
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
			float PlayerNorm = FMath::Clamp(PlayerDistance / MaxRadius, 0.f, 1.f);

			if (ActorDistance > MaxRadius)
			{
				// If this actor is farther from center than player, speed up
				float Dilation = FMath::Lerp(1.0f, MaxDilation, 1.0f - PlayerNorm);
				Actor->CustomTimeDilation = Dilation;
			}
			else
			{
				// If this actor is closer to center than player, slow down
				float Dilation = FMath::Lerp(MinDilation, 1.0f, ActorDistance / PlayerDistance);
				Actor->CustomTimeDilation = Dilation;
			}
		}
	}
}
