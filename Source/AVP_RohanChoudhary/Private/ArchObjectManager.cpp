// Fill out your copyright notice in the Description page of Project Settings.


#include "ArchObjectManager.h"
#include "ArchSelectableObject.h"

#include "Kismet/GameplayStatics.h"

AArchObjectManager::AArchObjectManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AArchObjectManager::BeginPlay()
{
	Super::BeginPlay();

	BuildObjectDatabase();
}

void AArchObjectManager::BuildObjectDatabase()
{
	TArray<AActor*> FoundActors;

	UGameplayStatics::GetAllActorsOfClass(
		GetWorld(),
		AArchSelectableObject::StaticClass(),
		FoundActors);

	for (AActor* Actor : FoundActors)
	{
		AArchSelectableObject* SelectableObject =
			Cast<AArchSelectableObject>(Actor);

		if (!SelectableObject)
		{
			continue;
		}

		const FArchObjectInfo Info =
			SelectableObject->GetObjectInfo();

		ObjectNames.Add(
			Info.ObjectID);

		ObjectDisplayNames.Add(
			Info.ObjectID,
			Info.DisplayName);

		if (
			SelectableObject->bSelected)
		{
			SelectedObjectIDs.Add(
				Info.ObjectID);
		}
	}
}


void AArchObjectManager::SelectObject(
	AArchSelectableObject* NewSelection)
{
	if (CurrentSelection == NewSelection)
	{
		return;
	}

	if (CurrentSelection)
	{
		CurrentSelection->SetSelectedState(false);

		SelectedObjectIDs.Remove(
			CurrentSelection
			->GetObjectInfo()
			.ObjectID);
	}

	CurrentSelection = NewSelection;

	if (CurrentSelection)
	{
		CurrentSelection->SetSelectedState(true);

		const FArchObjectInfo Info = CurrentSelection->GetObjectInfo();

		SelectedObjectIDs.Add(Info.ObjectID);

		// Broadcast selection events
		CurrentSelection->OnObjectSelected(Info);
		OnObjectSelected.Broadcast(Info);
	}
	else
	{
		// Broadcast empty selection
		FArchObjectInfo EmptyInfo;
		OnObjectSelected.Broadcast(EmptyInfo);
	}
}

AArchSelectableObject*
AArchObjectManager::GetCurrentSelection() const
{
	return CurrentSelection;
}

void AArchObjectManager::ToggleObjectIDs()
{
	bShowObjectIDs = !bShowObjectIDs;

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AArchSelectableObject::StaticClass(), FoundActors);

	for (AActor* Actor : FoundActors)
	{
		if (AArchSelectableObject* SelectableObject = Cast<AArchSelectableObject>(Actor))
		{
			SelectableObject->UpdateLabel();
		}
	}
}

bool AArchObjectManager::GetMetadataForObject(FName ObjectID, FArchObjectCSVRow& OutRow) const
{
	if (!ArchObjectDataTable)
	{
		return false;
	}

	static const FString ContextString(TEXT("ArchObjectManager CSV LookUp"));
	FArchObjectCSVRow* Row = ArchObjectDataTable->FindRow<FArchObjectCSVRow>(ObjectID, ContextString);
	if (Row)
	{
		OutRow = *Row;
		return true;
	}

	return false;
}