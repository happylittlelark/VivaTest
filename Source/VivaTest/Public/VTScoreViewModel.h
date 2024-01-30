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
	
protected:

private:
	UPROPERTY(BlueprintReadOnly, FieldNotify, Setter, Getter, meta=(AllowPrivateAccess))
	float Score;
	
};
