// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DesignOptionSwitcherWidget.generated.h"

class UButton;
class UTextBlock;

/**
 * UDesignOptionSwitcherWidget is a UI overlay that allows switching the active selected object
 * in the showroom, supporting keyboard and gamepad navigation.
 */
UCLASS()
class AVP_ROHANCHOUDHARY_API UDesignOptionSwitcherWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Option1;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Option2;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Option3;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_CurrentOption;

	UFUNCTION()
	void OnOption1Clicked();

	UFUNCTION()
	void OnOption2Clicked();

	UFUNCTION()
	void OnOption3Clicked();

	void SelectOptionIndex(int32 Index);

public:
	UFUNCTION(BlueprintCallable, Category = "ArchViz")
	void RefreshUI();

	UFUNCTION(BlueprintCallable, Category = "ArchViz")
	void FocusActiveOption();

	// Blueprint event overridden in WBP to style active/inactive states of buttons and text
	UFUNCTION(BlueprintImplementableEvent, Category = "ArchViz")
	void OnOptionSelectedChanged(int32 SelectedIndex, const FText& OptionLabel);
};
