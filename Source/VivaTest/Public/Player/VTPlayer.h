// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "VTPlayer.generated.h"

class UInputMappingContext;
class UInputAction;
class AVTProjectile;
class AAIController;
class AVTTankPawn;

UCLASS()
class VIVATEST_API AVTPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AVTPlayer();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void OnRep_Controller() override;
	void AddScore();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnTankPawnDestroyed();
	UFUNCTION()
	void SpawnTank();

	UFUNCTION(BlueprintCallable)
	void Zoom(const float Value);

	UFUNCTION(BlueprintCallable)
	FVector FindDeprojectedMouseLocation() const; 

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void ServerMoveToLocation(const FVector& NewLocation);
	
	UFUNCTION(Server, Unreliable, BlueprintCallable)
	void ServerSpawnProjectile();

	UFUNCTION()
	void FireWeapon();

	UFUNCTION()
	void ChooseMoveLocation();

	void SetViewTargetOnTank();

	UFUNCTION()
	void OnRep_TankPawn();
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AVTTankPawn> TankPawnClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AAIController> TankAIControllerClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AVTProjectile> ProjectileClass;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_TankPawn)
	TObjectPtr<AVTTankPawn> TankPawn;
	
	UPROPERTY(BlueprintReadOnly, Replicated)
	TObjectPtr<AAIController> TankAIController;

	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UInputMappingContext> InputMappingContext;
	
	UPROPERTY(EditDefaultsOnly)
	TMap<FName, TSoftObjectPtr<UInputAction>> InputActionMap;

};
