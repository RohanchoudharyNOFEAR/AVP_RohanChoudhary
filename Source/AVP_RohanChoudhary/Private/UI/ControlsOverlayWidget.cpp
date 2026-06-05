// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/ControlsOverlayWidget.h"
#include "Components/Button.h"

void UControlsOverlayWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (CloseButton)
	{
		CloseButton->OnClicked.AddDynamic(this, &UControlsOverlayWidget::OnCloseClicked);
	}
}

void UControlsOverlayWidget::OnCloseClicked()
{
	SetVisibility(ESlateVisibility::Collapsed);
}
