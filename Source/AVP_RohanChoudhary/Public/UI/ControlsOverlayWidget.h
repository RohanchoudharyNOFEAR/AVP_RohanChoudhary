// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ControlsOverlayWidget.generated.h"

class UButton;

/**
 * UI Widget class that displays a list of controls and keybindings (cheat sheet).
 */
UCLASS()
class AVP_ROHANCHOUDHARY_API UControlsOverlayWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	// Close button
	UPROPERTY(meta = (BindWidget))
	UButton* CloseButton;

	UFUNCTION()
	void OnCloseClicked();
};
