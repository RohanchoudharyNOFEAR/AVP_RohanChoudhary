// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/ReviewNotesWidget.h"
#include "Components/EditableTextBox.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "ArchObjectManager.h"
#include "ArchSelectableObject.h"
#include "BPL_ArchVizUtilities.h"
#include "Kismet/GameplayStatics.h"

void UReviewNotesWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (SaveButton)
	{
		SaveButton->OnClicked.AddDynamic(this, &UReviewNotesWidget::OnSaveClicked);
	}

	// Bind to the manager's selection delegate
	TArray<AActor*> FoundManagers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AArchObjectManager::StaticClass(), FoundManagers);
	if (FoundManagers.Num() > 0)
	{
		if (AArchObjectManager* Manager = Cast<AArchObjectManager>(FoundManagers[0]))
		{
			Manager->OnObjectSelected.AddUObject(this, &UReviewNotesWidget::HandleObjectSelected);

			// Pre-populate if an object is already selected
			if (AArchSelectableObject* Selected = Manager->GetCurrentSelection())
			{
				HandleObjectSelected(Selected->GetObjectInfo());
			}
		}
	}

	if (FeedbackText)
	{
		FeedbackText->SetText(FText::GetEmpty());
	}

	if (SelectedObjectInfoText && !bHasSelection)
	{
		SelectedObjectInfoText->SetText(FText::FromString(TEXT("Select an object to review")));
	}
}

void UReviewNotesWidget::HandleObjectSelected(const FArchObjectInfo& ObjectInfo)
{
	CurrentSelectedInfo = ObjectInfo;
	bHasSelection = true;

	if (SelectedObjectInfoText)
	{
		SelectedObjectInfoText->SetText(FText::Format(
			FText::FromString(TEXT("Reviewing: {0} ({1})")),
			CurrentSelectedInfo.DisplayName,
			FText::FromName(CurrentSelectedInfo.RoomName)
		));
	}

	if (FeedbackText)
	{
		FeedbackText->SetText(FText::GetEmpty());
	}
}

void UReviewNotesWidget::OnSaveClicked()
{
	if (!bHasSelection)
	{
		if (FeedbackText)
		{
			FeedbackText->SetText(FText::FromString(TEXT("Error: No object selected!")));
		}
		return;
	}

	FString Note = "";
	if (NoteInput)
	{
		Note = NoteInput->GetText().ToString();
	}

	if (Note.IsEmpty())
	{
		if (FeedbackText)
		{
			FeedbackText->SetText(FText::FromString(TEXT("Error: Note cannot be empty!")));
		}
		return;
	}

	FString OutMsg;
	bool bSuccess = UBPL_ArchVizUtilities::ExportReviewNoteToCSV(
		CurrentSelectedInfo.ObjectID.ToString(),
		CurrentSelectedInfo.DisplayName.ToString(),
		CurrentSelectedInfo.RoomName.ToString(),
		Note,
		OutMsg
	);

	if (FeedbackText)
	{
		FeedbackText->SetText(FText::FromString(OutMsg));
	}

	if (bSuccess && NoteInput)
	{
		NoteInput->SetText(FText::GetEmpty());
	}
}
