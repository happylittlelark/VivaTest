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

	UFUNCTION(BlueprintPure, FieldNotify)
	float GetScore() const;
	UFUNCTION()
	void SetScore(const float NewScore);

	UFUNCTION(BlueprintPure, FieldNotify)
	const FString& GetPlayerName() const;
	UFUNCTION()
	void SetPlayerName(const FString& NewPlayerName);
	
protected:

private:
	UPROPERTY(BlueprintReadOnly, FieldNotify, Setter, Getter, meta=(AllowPrivateAccess))
	float Score;
	
	UPROPERTY(BlueprintReadOnly, FieldNotify, Setter, Getter, meta=(AllowPrivateAccess))
	FString PlayerName;
	
};
