// Fill out your copyright notice in the Description page of Project Settings.


#include "VTProjectile.h"

#include <Components/BoxComponent.h>

#include <Engine/DamageEvents.h>

#include <GameFramework/ProjectileMovementComponent.h>

#include "VTPlayer.h"

// Sets default values
AVTProjectile::AVTProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("Movement Component");
	Body = CreateDefaultSubobject<UStaticMeshComponent>("Body");
	
	CollisionComponent = CreateDefaultSubobject<UBoxComponent>("Collision");
	SetRootComponent(CollisionComponent);

	Body->SetupAttachment(CollisionComponent);

	bReplicates = true;
	SetReplicateMovement(true);
}

// Called when the game starts or when spawned
void AVTProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void AVTProjectile::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	
	MovementComponent->OnProjectileStop.RemoveDynamic(this, &ThisClass::OnProjectileStop);
}

void AVTProjectile::OnProjectileStop(const FHitResult& HitResult)
{
	if (!HitResult.bBlockingHit)
	{
		return;
	}

	AActor* HitActor = HitResult.GetActor();
	
	if (IsValid(HitActor) && HitActor->CanBeDamaged())
	{
		const FPointDamageEvent DamageEvent = FPointDamageEvent(Damage, HitResult, GetActorForwardVector(), DamageType);
		const float ActualDamage = HitActor->TakeDamage(Damage, DamageEvent, GetInstigatorController(), this);

		if (ActualDamage > 0)
		{
			AVTPlayer* Player = GetInstigator<AVTPlayer>();
			if (IsValid(Player))
			{
				Player->AddScore();
			}
		}
	}

	Destroy();
}

void AVTProjectile::Fire(const float Force) const
{
	MovementComponent->AddForce(Force * GetActorForwardVector());

	MovementComponent->OnProjectileStop.AddDynamic(this, &ThisClass::OnProjectileStop);
}

