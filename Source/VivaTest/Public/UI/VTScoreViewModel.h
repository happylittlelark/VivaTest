// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "VTScoreViewModel.generated.h"

/**
 * 
 */
UCLASS()
class VIVATEST_API UVTScoreViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:

	float GetScore() const;
	void SetScore(const float NewScore);

	const FString& GetPlayerName() const;
	void SetPlayerName(const FString& NewPlayerName);
	
private:
	UPROPERTY(BlueprintReadOnly, FieldNotify, Setter, Getter, meta=(AllowPrivateAccess))
	float Score;
	
	UPROPERTY(BlueprintReadOnly, FieldNotify, Setter, Getter, meta=(AllowPrivateAccess))
	FString PlayerName;
	
};
