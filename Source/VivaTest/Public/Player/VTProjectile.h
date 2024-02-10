// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VTProjectile.generated.h"

class UBoxComponent;
class UProjectileMovementComponent;
UCLASS()
class VIVATEST_API AVTProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVTProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	UFUNCTION()
	void OnProjectileStop(const FHitResult& HitResult);

public:	
	void Fire(const float Force) const;

private:
	UPROPERTY(Category=Projectile, VisibleAnywhere, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> Body;
	
	UPROPERTY(Category=Projectile, VisibleAnywhere, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UBoxComponent> CollisionComponent;

	UPROPERTY(Category=Projectile, VisibleAnywhere, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UProjectileMovementComponent> MovementComponent;

	UPROPERTY(Category=Projectile, VisibleAnywhere, meta=(AllowPrivateAccess = "true"))
	TSubclassOf<UDamageType> DamageType;

	UPROPERTY(Category=Projectile, VisibleAnywhere, meta=(AllowPrivateAccess = "true"))
	float Damage = 10.f;
};
