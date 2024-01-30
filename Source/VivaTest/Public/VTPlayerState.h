// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "VTPlayerState.generated.h"

class UVTScoreViewModel;

/**
 * 
 */
UCLASS()
class VIVATEST_API AVTPlayerState : public APlayerState
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;

	virtual void OnRep_Score() override;
	
	void ScorePoint();

	UFUNCTION(Client, Unreliable)
	void ClientInitialiseScoreWidget(APlayerState* PlayerState);


protected:

	UPROPERTY()
	TObjectPtr<UVTScoreViewModel> ScoreViewModel;

	
};
