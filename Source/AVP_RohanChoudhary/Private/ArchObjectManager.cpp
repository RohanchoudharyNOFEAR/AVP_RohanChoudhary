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
			SelectableObject->bSelected ||
			SelectableObject->bHighlighted)
		{
			SelectedObjectIDs.Add(
				Info.ObjectID);
		}
	}
	FString DebugText;

	DebugText += TEXT("Object List\n\n");

	for (const FName& ObjectName : ObjectNames)
	{
		DebugText +=
			ObjectName.ToString();

		DebugText += TEXT("\n");
	}

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			20.f,
			FColor::Cyan,
			DebugText);
	}
}
