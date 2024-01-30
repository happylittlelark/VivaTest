// Fill out your copyright notice in the Description page of Project Settings.


#include "VTPlayerStart.h"

#include <Components/SphereComponent.h>

AVTPlayerStart::AVTPlayerStart(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	ProximitySensor = CreateDefaultSubobject<USphereComponent>("Proximity Sensor");
	ProximitySensor->SetupAttachment(GetRootComponent());

	Tags.AddUnique(AVTPlayerStart::ActiveTag);
}

void AVTPlayerStart::OnProximityOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	Tags.Remove(AVTPlayerStart::ActiveTag);
}

void AVTPlayerStart::OnProximityOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Tags.AddUnique(AVTPlayerStart::ActiveTag);
}

void AVTPlayerStart::BeginPlay()
{
	Super::BeginPlay();

	ProximitySensor->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnProximityOverlapBegin);
	ProximitySensor->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnProximityOverlapEnd);

	Tags.AddUnique(AVTPlayerStart::ActiveTag);
}

void AVTPlayerStart::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	ProximitySensor->OnComponentBeginOverlap.RemoveDynamic(this, &ThisClass::OnProximityOverlapBegin);
	ProximitySensor->OnComponentEndOverlap.RemoveDynamic(this, &ThisClass::OnProximityOverlapEnd);
}
