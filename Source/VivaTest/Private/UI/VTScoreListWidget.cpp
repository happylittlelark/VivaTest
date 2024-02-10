// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/VTScoreListWidget.h"

#include "CommonListView.h"
#include "UI/VTScoreViewModel.h"


void UVTScoreListWidget::AddScoreWidget(UVTScoreViewModel* ViewModel) const
{
	PlayerListView->AddItem(ViewModel);
}
