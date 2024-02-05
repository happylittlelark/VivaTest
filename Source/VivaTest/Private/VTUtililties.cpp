// Fill out your copyright notice in the Description page of Project Settings.


#include <MVVMSubsystem.h>

#include <Blueprint/UserWidget.h>

#include <View/MVVMView.h>

#include "VivaTest/Public/VTUtilities.h"

void UVTUtilities::SetViewModel(const UUserWidget* UserWidget, const FName& Name, UMVVMViewModelBase* ViewModel)
{
	if (!IsValid(UserWidget))
	{
		return;
	}

	if (!IsValid(GEngine))
	{
		return;
	}
	
	const UMVVMSubsystem* MVVMSubsystem = GEngine->GetEngineSubsystem<UMVVMSubsystem>();

	if (!IsValid(MVVMSubsystem))
	{
		return;
	}

	UMVVMView* View = MVVMSubsystem->GetViewFromUserWidget(UserWidget);

	if (!IsValid(View))
	{
		return;
	}
	
	View->SetViewModel(Name, ViewModel);
}

