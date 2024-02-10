// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/VTGameState.h"
#include "Player/VTPlayerState.h"
#include "GameFramework/PlayerState.h"

void AVTGameState::AddPlayerState(APlayerState* PlayerState)
{
	Super::AddPlayerState(PlayerState);
	
	const bool bHasAuthority = HasAuthority();

	if (!bHasAuthority)
	{
		AVTPlayerState* VTPlayerState = Cast<AVTPlayerState>(PlayerState);
		
		if (!IsValid(VTPlayerState))
		{
			return;
		}
		
		for (APlayerState* Player : PlayerArray)
		{
			VTPlayerState->ClientInitialiseScoreWidget(PlayerState);
		}
	}
}
