// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/DesignOptionSwitcherWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "ArchObjectManager.h"
#include "ArchSelectableObject.h"
#include "Kismet/GameplayStatics.h"

void UDesignOptionSwitcherWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (Button_Option1)
	{
		Button_Option1->OnClicked.AddDynamic(this, &UDesignOptionSwitcherWidget::OnOption1Clicked);
	}
	if (Button_Option2)
	{
		Button_Option2->OnClicked.AddDynamic(this, &UDesignOptionSwitcherWidget::OnOption2Clicked);
	}
	if (Button_Option3)
	{
		Button_Option3->OnClicked.AddDynamic(this, &UDesignOptionSwitcherWidget::OnOption3Clicked);
	}

	RefreshUI();
}

void UDesignOptionSwitcherWidget::OnOption1Clicked()
{
	SelectOptionIndex(0);
}

void UDesignOptionSwitcherWidget::OnOption2Clicked()
{
	SelectOptionIndex(1);
}

void UDesignOptionSwitcherWidget::OnOption3Clicked()
{
	SelectOptionIndex(2);
}

void UDesignOptionSwitcherWidget::SelectOptionIndex(int32 Index)
{
	TArray<AActor*> FoundManagers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AArchObjectManager::StaticClass(), FoundManagers);
	if (FoundManagers.Num() == 0)
	{
		return;
	}

	AArchObjectManager* Manager = Cast<AArchObjectManager>(FoundManagers[0]);
	if (!Manager)
	{
		return;
	}

	FName TargetID = NAME_None;
	if (Index == 0) TargetID = TEXT("Chair01");
	else if (Index == 1) TargetID = TEXT("Table01");
	else if (Index == 2) TargetID = TEXT("Chair02");

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AArchSelectableObject::StaticClass(), FoundActors);

	AArchSelectableObject* TargetObject = nullptr;
	for (AActor* Actor : FoundActors)
	{
		if (AArchSelectableObject* Selectable = Cast<AArchSelectableObject>(Actor))
		{
			if (Selectable->GetObjectInfo().ObjectID == TargetID)
			{
				TargetObject = Selectable;
				break;
			}
		}
	}

	if (TargetObject)
	{
		Manager->SelectObject(TargetObject);
	}

	RefreshUI();
}

void UDesignOptionSwitcherWidget::RefreshUI()
{
	TArray<AActor*> FoundManagers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AArchObjectManager::StaticClass(), FoundManagers);
	if (FoundManagers.Num() == 0)
	{
		return;
	}

	AArchObjectManager* Manager = Cast<AArchObjectManager>(FoundManagers[0]);
	if (!Manager)
	{
		return;
	}

	AArchSelectableObject* Selected = Manager->GetCurrentSelection();
	int32 SelectedIndex = -1;
	FText OptionLabel = FText::FromString(TEXT("None (Click an option to focus layout)"));

	if (Selected)
	{
		FName SelectedID = Selected->GetObjectInfo().ObjectID;
		FText DisplayName = Selected->GetObjectInfo().DisplayName;

		if (SelectedID == TEXT("Chair01"))
		{
			SelectedIndex = 0;
			OptionLabel = FText::Format(FText::FromString(TEXT("Luxury Armchair ({0})")), DisplayName);
		}
		else if (SelectedID == TEXT("Table01"))
		{
			SelectedIndex = 1;
			OptionLabel = FText::Format(FText::FromString(TEXT("Round Dining Table ({0})")), DisplayName);
		}
		else if (SelectedID == TEXT("Chair02"))
		{
			SelectedIndex = 2;
			OptionLabel = FText::Format(FText::FromString(TEXT("Ergonomic Office Chair ({0})")), DisplayName);
		}
		else
		{
			OptionLabel = FText::Format(FText::FromString(TEXT("{0} (Active Focus)")), DisplayName);
		}
	}

	if (Text_CurrentOption)
	{
		Text_CurrentOption->SetText(OptionLabel);
	}

	OnOptionSelectedChanged(SelectedIndex, OptionLabel);
}

void UDesignOptionSwitcherWidget::FocusActiveOption()
{
	TArray<AActor*> FoundManagers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AArchObjectManager::StaticClass(), FoundManagers);
	if (FoundManagers.Num() > 0)
	{
		if (AArchObjectManager* Manager = Cast<AArchObjectManager>(FoundManagers[0]))
		{
			if (AArchSelectableObject* Selected = Manager->GetCurrentSelection())
			{
				FName SelectedID = Selected->GetObjectInfo().ObjectID;
				if (SelectedID == TEXT("Chair01") && Button_Option1)
				{
					Button_Option1->SetFocus();
					return;
				}
				else if (SelectedID == TEXT("Table01") && Button_Option2)
				{
					Button_Option2->SetFocus();
					return;
				}
				else if (SelectedID == TEXT("Chair02") && Button_Option3)
				{
					Button_Option3->SetFocus();
					return;
				}
			}
		}
	}

	// Default focus fallback
	if (Button_Option1)
	{
		Button_Option1->SetFocus();
	}
}
