// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/ArchObjectTypes.h"
#include "ReviewNotesWidget.generated.h"

class UEditableTextBox;
class UButton;
class UTextBlock;

/**
 * Custom Widget class to allow entering and saving review notes to CSV
 */
UCLASS()
class AVP_ROHANCHOUDHARY_API UReviewNotesWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* NoteInput;

	UPROPERTY(meta = (BindWidget))
	UButton* SaveButton;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* FeedbackText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* SelectedObjectInfoText;

	UFUNCTION()
	void OnSaveClicked();

	UFUNCTION()
	void HandleObjectSelected(const FArchObjectInfo& ObjectInfo);

private:
	FArchObjectInfo CurrentSelectedInfo;
	bool bHasSelection = false;
};
