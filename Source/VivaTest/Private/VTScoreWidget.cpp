// Fill out your copyright notice in the Description page of Project Settings.


#include "VTScoreWidget.h"

#include <Components/TextBlock.h>

#include "CommonNumericTextBlock.h"
#include "VTScoreViewModel.h"
#include "VTUtilities.h"

void UVTScoreWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	UVTScoreViewModel* ViewModel = Cast<UVTScoreViewModel>(ListItemObject);

	if (!IsValid(ViewModel))
	{
		return;
	}
	
	UVTUtilities::SetViewModel(this, TEXT("VTScoreViewModel"), ViewModel);
}

void UVTScoreWidget::SetScore(const float NewScore)
{
	if (!IsValid(Score))
	{
		return;
	}

	Score->SetCurrentValue(NewScore);
}

void UVTScoreWidget::SetName(const FString& NewName)
{
	if (!IsValid(Name))
	{
		return;
	}
	
	Name->SetText(FText::FromString(NewName));
}
