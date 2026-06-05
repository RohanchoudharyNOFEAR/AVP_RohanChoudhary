// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/ArchObjectTypes.h"
#include "ObjectInfoPanelWidget.generated.h"

class UTextBlock;
class UButton;
class UWidget;

/**
 * UI Widget class that displays selection information and metadata for architectural objects.
 */
UCLASS()
class AVP_ROHANCHOUDHARY_API UObjectInfoPanelWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	// Object details bindings
	UPROPERTY(meta = (BindWidget))
	UTextBlock* DisplayNameText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* CategoryText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* RoomNameText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* AreaText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* DescriptionText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* MaterialGroupText;

	// Placeholders
	UPROPERTY(meta = (BindWidget))
	UWidget* MaterialOptionPlaceHolder;

	UPROPERTY(meta = (BindWidget))
	UWidget* ReviewNotesPlaceHolder;

	// View containers
	UPROPERTY(meta = (BindWidget))
	UWidget* InfoContainer;

	UPROPERTY(meta = (BindWidget))
	UWidget* EmptyStateContainer;

	// Main Panel Root for visibility toggling
	UPROPERTY(meta = (BindWidget))
	UWidget* MainPanelBorder;

	// Collapse button
	UPROPERTY(meta = (BindWidget))
	UButton* CloseButton;

	UFUNCTION()
	void OnCloseClicked();

	UFUNCTION()
	void HandleObjectSelected(const FArchObjectInfo& ObjectInfo);

private:
	void ShowEmptyState();
};
