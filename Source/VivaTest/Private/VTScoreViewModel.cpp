// Fill out your copyright notice in the Description page of Project Settings.


#include "VTScoreViewModel.h"

float UVTScoreViewModel::GetScore() const
{
	return Score;
}

void UVTScoreViewModel::SetScore(const float NewScore)
{
	UE_MVVM_SET_PROPERTY_VALUE(Score, NewScore);
}

const FString& UVTScoreViewModel::GetName() const
{
	return Name;
}

void UVTScoreViewModel::SetName(const FString& NewName)
{
	UE_MVVM_SET_PROPERTY_VALUE(Name, NewName);
}
