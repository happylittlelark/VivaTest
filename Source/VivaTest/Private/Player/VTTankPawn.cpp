// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/VTTankPawn.h"
#include "GameplayTasksComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AVTTankPawn::AVTTankPawn(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Chassis = CreateDefaultSubobject<UStaticMeshComponent>("Chassis");
	Chassis->SetupAttachment(GetRootComponent());

	GunPivot = CreateDefaultSubobject<USceneComponent>("Gun Pivot");
	GunPivot->SetupAttachment(GetRootComponent());

	Barrel = CreateDefaultSubobject<UStaticMeshComponent>("Barrel");
	Barrel->SetupAttachment(GunPivot);
	
	MuzzlePoint = CreateDefaultSubobject<USceneComponent>("Muzzle Point");
	MuzzlePoint->SetupAttachment(Barrel);
	
	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>("Camera Spring Arm");
	CameraSpringArm->SetupAttachment(GetRootComponent());

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(CameraSpringArm);

	TaskComponent = CreateDefaultSubobject<UGameplayTasksComponent>("Task Component");

	bReplicates = true;
	SetReplicateMovement(true);
}

FTransform AVTTankPawn::GetProjectileSpawnTransform() const
{
	if (IsValid(MuzzlePoint))
	{
		return MuzzlePoint->GetComponentTransform();
	}

	return GetActorTransform();
}

void AVTTankPawn::Zoom(const float Value) const
{
	CameraSpringArm->SocketOffset.Z += Value;
}

const FTransform& AVTTankPawn::GetCameraTransform() const
{
	if (IsValid(Camera))
	{
		return Camera->GetComponentTransform();
	}

	return GetActorTransform();
}

void AVTTankPawn::TankPawnDied()
{
	Destroy();

	OnTankPawnDestroyed.Broadcast();
}

float AVTTankPawn::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (!HasAuthority())
	{
		return 0.0f;
	}
	
	const float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	CurrentHealth -= ActualDamage;

	CurrentHealth = FMath::Clamp(CurrentHealth, 0.0f, MaxHealth);

	if (FMath::IsNearlyEqual(CurrentHealth, 0.f) || CurrentHealth < 0.f)
	{
		TankPawnDied();
	}

	return ActualDamage;
}

