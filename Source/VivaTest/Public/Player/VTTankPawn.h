// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include <GameFramework/Character.h>

#include "VTTankPawn.generated.h"

class UGameplayTasksComponent;
class USpringArmComponent;
class UCameraComponent;
class UBoxComponent;
class UShapeComponent;
class USceneComponent;

DECLARE_MULTICAST_DELEGATE(FOnTankPawnDestroyedSignature)

UCLASS()
class VIVATEST_API AVTTankPawn : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AVTTankPawn(const FObjectInitializer& ObjectInitializer);

	FTransform GetProjectileSpawnTransform() const;
	void Zoom(const float Value) const;
	const FTransform& GetCameraTransform() const;

	void TankPawnDied();
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	FOnTankPawnDestroyedSignature OnTankPawnDestroyed;

private:
	UPROPERTY(Category=Character, VisibleAnywhere, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> Chassis;
	
	UPROPERTY(Category=Character, VisibleAnywhere, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> Barrel;

	// In a proper implementation I would use a socket on a custom mesh but since I'm using primitive shapes I thought this would be ok
	UPROPERTY(Category=Character, VisibleAnywhere, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> MuzzlePoint;
	
	UPROPERTY(Category=Character, VisibleAnywhere, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> GunPivot;

	UPROPERTY(Category=Character, VisibleAnywhere, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraSpringArm;
	
	UPROPERTY(Category=Character, VisibleAnywhere, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> Camera;
	
	UPROPERTY(Category=Character, VisibleAnywhere, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UGameplayTasksComponent> TaskComponent;

	UPROPERTY(Category=Character, EditDefaultsOnly, meta=(AllowPrivateAccess = "true"))
	float MaxHealth = 10.f;

	UPROPERTY(Category=Character, EditDefaultsOnly, meta=(AllowPrivateAccess = "true"))
	float CurrentHealth = 10.f;

};
