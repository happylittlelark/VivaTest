// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerStart.h"
#include "VTPlayerStart.generated.h"

class USphereComponent;
/**
 * 
 */
UCLASS()
class VIVATEST_API AVTPlayerStart : public APlayerStart
{
	GENERATED_BODY()

public:
	AVTPlayerStart(const FObjectInitializer& ObjectInitializer);

	UFUNCTION()
	void OnProximityOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnProximityOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	inline static FName ActiveTag = TEXT("ActivePlayerStart");

protected:
	UPROPERTY(VisibleAnywhere, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USphereComponent> ProximitySensor;

};
