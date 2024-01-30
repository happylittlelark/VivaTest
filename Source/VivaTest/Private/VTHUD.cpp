// Fill out your copyright notice in the Description page of Project Settings.


#include "VTHUD.h"
#include "VTScoreListWidget.h"
#include "VTScoreViewModel.h"

void AVTHUD::InitialiseScore(UVTScoreViewModel* ScoreViewModel)
{
	if (!IsValid(ScoreViewModel))
	{
		return;
	}
	
	if (!IsValid(ScoreListWidget))
	{
		ScoreListWidget = CreateWidget<UVTScoreListWidget>(GetOwningPlayerController(), ScoreListWidgetClass.LoadSynchronous());
	
		if (!IsValid(ScoreListWidget))
		{
			return;
		}
	
		ScoreListWidget->AddToViewport();
		
		ScoreListWidget->AddScoreWidget(ScoreViewModel);
	}
	else
	{
		ScoreListWidget->AddScoreWidget(ScoreViewModel);
	}
}
