// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include <Blueprint/IUserObjectListEntry.h>
#include "Blueprint/UserWidget.h"
#include "VTScoreWidget.generated.h"

class UTextBlock;
class UCommonNumericTextBlock;
class UVTScoreViewModel;
/**
 * 
 */
UCLASS(Abstract)
class VIVATEST_API UVTScoreWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

public:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	UFUNCTION(BlueprintCallable)
	void SetScore(const float NewScore);
	UFUNCTION(BlueprintCallable)
	void SetName(const FString& NewName);
	
	UFUNCTION(BlueprintImplementableEvent)
	UVTScoreViewModel* GetViewModel() const;
	
protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Name;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonNumericTextBlock> Score;
};
