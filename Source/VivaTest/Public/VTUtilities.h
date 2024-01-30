// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "VTUtilities.generated.h"

class UMVVMViewModelBase;
/**
 * 
 */
UCLASS()
class VIVATEST_API UVTUtilities : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static void SetViewModel(const UUserWidget* UserWidget, const FName& Name, UMVVMViewModelBase* ViewModel);
};
