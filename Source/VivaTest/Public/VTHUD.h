// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "VTHUD.generated.h"

class UVTScoreViewModel;
class UVTScoreWidget;
class UVTScoreListWidget;

/**
 * 
 */
UCLASS(Abstract)
class VIVATEST_API AVTHUD : public AHUD
{
	GENERATED_BODY()

public:
	void InitialiseScore(UVTScoreViewModel* ScoreViewModel);

	UPROPERTY(EditDefaultsOnly)
	TSoftClassPtr<UVTScoreWidget> ScoreWidgetClass;
	UPROPERTY(EditDefaultsOnly)
	TSoftClassPtr<UVTScoreListWidget> ScoreListWidgetClass;
	
protected:
	// UPROPERTY(Transient)
	// TObjectPtr<UVTScoreWidget> ScoreWidget;
	UPROPERTY(Transient)
	TObjectPtr<UVTScoreListWidget> ScoreListWidget;
};
