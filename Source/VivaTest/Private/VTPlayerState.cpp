// Fill out your copyright notice in the Description page of Project Settings.


#include "VTPlayerState.h"

#include "VTHUD.h"
#include "VTScoreViewModel.h"

void AVTPlayerState::BeginPlay()
{
	Super::BeginPlay();
}

void AVTPlayerState::OnRep_Score()
{
	Super::OnRep_Score();

	if (!IsValid(ScoreViewModel))
	{
		return;
	}
	
	const APlayerController* PlayerController = GetPlayerController();

	if (!IsValid(PlayerController) || !PlayerController->IsLocalController())
	{
		return;
	}

	ScoreViewModel->SetScore(GetScore());
}

void AVTPlayerState::ScorePoint()
{
	if (!HasAuthority())
	{
		return;
	}
	
	const float NewScore = GetScore() + 1.f;
	
	SetScore(NewScore);

	if (!IsValid(ScoreViewModel))
	{
		return;
	}

	const APlayerController* PlayerController = GetPlayerController();

	if (!IsValid(PlayerController) || !HasAuthority())
	{
		return;
	}
	
	ScoreViewModel->SetScore(GetScore());
}

void AVTPlayerState::ClientInitialiseScoreWidget_Implementation(APlayerState* PlayerState)
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController<APlayerController>();

	if (!IsValid(PlayerController))
	{
		return;
	}

	AVTHUD* HUD = PlayerController->GetHUD<AVTHUD>();
	
	if (!IsValid(HUD))
	{
		return;
	}

	ScoreViewModel = NewObject<UVTScoreViewModel>(this);

	if (!IsValid(ScoreViewModel))
	{
		return;
	}
	
	HUD->InitialiseScore(ScoreViewModel);
}
