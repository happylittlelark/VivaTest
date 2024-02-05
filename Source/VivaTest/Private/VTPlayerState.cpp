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
	
	ScoreViewModel->SetScore(GetScore());
}

void AVTPlayerState::OnRep_PlayerName()
{
	Super::OnRep_PlayerName();

	if (!IsValid(ScoreViewModel))
	{
		return;
	}
	
	ScoreViewModel->SetName(GetPlayerName());
}

void AVTPlayerState::ScorePoint()
{
	if (!HasAuthority())
	{
		return;
	}
	
	const float NewScore = GetScore() + 1.f;
	
	SetScore(NewScore);
}

void AVTPlayerState::ClientInitialiseScoreWidget_Implementation(APlayerState* PlayerState)
{
	const APlayerController* PlayerController = GetWorld()->GetFirstPlayerController<APlayerController>();

	if (!IsValid(PlayerController))
	{
		return;
	}

	AVTHUD* HUD = PlayerController->GetHUD<AVTHUD>();
	
	if (!IsValid(HUD))
	{
		return;
	}

	// Already created, don't recreate
	if (IsValid(ScoreViewModel))
	{
		return;
	}

	ScoreViewModel = NewObject<UVTScoreViewModel>(this);

	if (!IsValid(ScoreViewModel))
	{
		return;
	}

	ScoreViewModel->SetScore(PlayerState->GetScore());
	ScoreViewModel->SetName(PlayerState->GetPlayerName());
	
	HUD->InitialiseScore(ScoreViewModel);
}
