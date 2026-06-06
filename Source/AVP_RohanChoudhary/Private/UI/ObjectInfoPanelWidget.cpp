// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/ObjectInfoPanelWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/Widget.h"
#include "ArchObjectManager.h"
#include "ArchSelectableObject.h"
#include "Kismet/GameplayStatics.h"

void UObjectInfoPanelWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (CloseButton)
	{
		CloseButton->OnClicked.AddDynamic(this, &UObjectInfoPanelWidget::OnCloseClicked);
	}

	// Bind to the manager's selection delegate
	TArray<AActor*> FoundManagers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AArchObjectManager::StaticClass(), FoundManagers);
	if (FoundManagers.Num() > 0)
	{
		if (AArchObjectManager* Manager = Cast<AArchObjectManager>(FoundManagers[0]))
		{
			Manager->OnObjectSelected.AddUObject(this, &UObjectInfoPanelWidget::HandleObjectSelected);

			// Pre-populate if an object is already selected
			if (AArchSelectableObject* Selected = Manager->GetCurrentSelection())
			{
				HandleObjectSelected(Selected->GetObjectInfo());
			}
			else
			{
				ShowEmptyState();
				if (MainPanelBorder)
				{
					MainPanelBorder->SetVisibility(ESlateVisibility::Collapsed);
				}
			}
		}
	}
	else
	{
		ShowEmptyState();
		if (MainPanelBorder)
		{
			MainPanelBorder->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}

void UObjectInfoPanelWidget::HandleObjectSelected(const FArchObjectInfo& ObjectInfo)
{
	// If no object is selected (empty ID)
	if (ObjectInfo.ObjectID.IsNone())
	{
		ShowEmptyState();
		if (MainPanelBorder)
		{
			MainPanelBorder->SetVisibility(ESlateVisibility::Collapsed);
		}
		return;
	}

	// Restore panel visibility if it was closed
	if (MainPanelBorder)
	{
		MainPanelBorder->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}

	// Switch from empty state to info display
	if (EmptyStateContainer)
	{
		EmptyStateContainer->SetVisibility(ESlateVisibility::Collapsed);
	}
	if (InfoContainer)
	{
		InfoContainer->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}

	// Populate metadata fields
	TArray<AActor*> FoundManagers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AArchObjectManager::StaticClass(), FoundManagers);
	if (FoundManagers.Num() > 0)
	{
		if (AArchObjectManager* Manager = Cast<AArchObjectManager>(FoundManagers[0]))
		{
			FArchObjectCSVRow CSVRow;
			if (Manager->GetMetadataForObject(ObjectInfo.ObjectID, CSVRow))
			{
				if (DisplayNameText)
				{
					DisplayNameText->SetText(CSVRow.DisplayName);
				}
				if (CategoryText)
				{
					CategoryText->SetText(UEnum::GetDisplayValueAsText(CSVRow.Category));
				}
				if (RoomNameText)
				{
					RoomNameText->SetText(FText::FromName(CSVRow.RoomName));
				}
				if (AreaText)
				{
					AreaText->SetText(FText::Format(
						FText::FromString(TEXT("{0} sq m")),
						FText::AsNumber(CSVRow.AreaSqM)
					));
				}
				if (DescriptionText)
				{
					DescriptionText->SetText(FText::FromString(CSVRow.Description));
				}
				if (MaterialGroupText)
				{
					MaterialGroupText->SetText(FText::FromName(CSVRow.MaterialGroup));
				}
				return;
			}
		}
	}

	// Fallback to basic object info if CSV is not found
	if (DisplayNameText)
	{
		DisplayNameText->SetText(ObjectInfo.DisplayName);
	}
	if (CategoryText)
	{
		CategoryText->SetText(UEnum::GetDisplayValueAsText(ObjectInfo.Category));
	}
	if (RoomNameText)
	{
		RoomNameText->SetText(FText::FromName(ObjectInfo.RoomName));
	}
	if (AreaText)
	{
		AreaText->SetText(FText::FromString(TEXT("N/A")));
	}
	if (DescriptionText)
	{
		DescriptionText->SetText(FText::FromString(TEXT("No description available.")));
	}
	if (MaterialGroupText)
	{
		MaterialGroupText->SetText(FText::FromName(ObjectInfo.MaterialGroup));
	}
}

void UObjectInfoPanelWidget::OnCloseClicked()
{
	if (MainPanelBorder)
	{
		MainPanelBorder->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UObjectInfoPanelWidget::ShowEmptyState()
{
	if (InfoContainer)
	{
		InfoContainer->SetVisibility(ESlateVisibility::Collapsed);
	}
	if (EmptyStateContainer)
	{
		EmptyStateContainer->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
}
