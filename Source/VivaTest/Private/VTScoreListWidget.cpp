// Fill out your copyright notice in the Description page of Project Settings.


#include "VTScoreListWidget.h"

#include <CommonListView.h>
#include "VTScoreViewModel.h"


void UVTScoreListWidget::AddScoreWidget(UVTScoreViewModel* ViewModel) const
{
	PlayerListView->AddItem(ViewModel);
}
