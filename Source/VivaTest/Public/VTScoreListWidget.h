// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "VTScoreListWidget.generated.h"

class UVTScoreViewModel;
class UListView;
/**
 * 
 */
UCLASS(Abstract)
class VIVATEST_API UVTScoreListWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void AddScoreWidget(UVTScoreViewModel* ViewModel) const;

protected:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UListView> PlayerListView;
	
};
