// Fill out your copyright notice in the Description page of Project Settings.


#include "ArchSelectableObject.h"

#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "ArchObjectManager.h"
#include "BPL_ArchVizUtilities.h"
#include "Kismet/GameplayStatics.h"
#include "ArchObjectInfoComponent.h"

AArchSelectableObject::AArchSelectableObject()
{
	Root =
		CreateDefaultSubobject<USceneComponent>(
			TEXT("Root"));

	RootComponent = Root;

	Mesh =
		CreateDefaultSubobject<UStaticMeshComponent>(
			TEXT("Mesh"));

	Mesh->SetupAttachment(Root);

	LabelText =
		CreateDefaultSubobject<UTextRenderComponent>(
			TEXT("LabelText"));

	LabelText->SetupAttachment(Root);

	LabelText->SetRelativeLocation(
		FVector(0.f, 0.f, 150.f));

	LabelText->SetHorizontalAlignment(
		EHorizTextAligment::EHTA_Center);

	LabelText->SetWorldSize(30.f);

	ObjectInfoComponent =
		CreateDefaultSubobject<UArchObjectInfoComponent>(
			TEXT("ObjectInfoComponent"));
}

void AArchSelectableObject::OnConstruction(
	const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (ObjectInfoComponent)
	{
		if (ObjectInfoComponent->ObjectID.IsNone() && !ArchObjectInfo.ObjectID.IsNone())
		{
			ObjectInfoComponent->ObjectID = ArchObjectInfo.ObjectID;
			ObjectInfoComponent->DisplayName = ArchObjectInfo.DisplayName;
			ObjectInfoComponent->Category = ArchObjectInfo.Category;
			ObjectInfoComponent->RoomName = ArchObjectInfo.RoomName;
		}
		else
		{
			ArchObjectInfo.ObjectID = ObjectInfoComponent->ObjectID;
			ArchObjectInfo.DisplayName = ObjectInfoComponent->DisplayName;
			ArchObjectInfo.Category = ObjectInfoComponent->Category;
			ArchObjectInfo.RoomName = ObjectInfoComponent->RoomName;
		}
	}

	UpdateLabel();
	UpdateVisualState();
}

void AArchSelectableObject::UpdateLabel()
{
	bool bShowID = true;

	if (UWorld* World = GetWorld())
	{
		TArray<AActor*> FoundManagers;
		UGameplayStatics::GetAllActorsOfClass(World, AArchObjectManager::StaticClass(), FoundManagers);
		if (FoundManagers.Num() > 0)
		{
			if (AArchObjectManager* Manager = Cast<AArchObjectManager>(FoundManagers[0]))
			{
				bShowID = Manager->IsShowingObjectIDs();
			}
		}
	}

	FName DisplayID = ObjectInfoComponent ? ObjectInfoComponent->ObjectID : ArchObjectInfo.ObjectID;
	FText DisplayNameVal = ObjectInfoComponent ? ObjectInfoComponent->DisplayName : ArchObjectInfo.DisplayName;

	FString LabelString;
	if (bShowID)
	{
		LabelString = FString::Printf(
			TEXT("%s\n%s"),
			*DisplayID.ToString(),
			*DisplayNameVal.ToString());
	}
	else
	{
		LabelString = FString::Printf(
			TEXT("%s"),
			*DisplayNameVal.ToString());
	}

	LabelText->SetText(FText::FromString(LabelString));
}

FArchObjectInfo
AArchSelectableObject::GetObjectInfo() const
{
	return ArchObjectInfo;
}



void AArchSelectableObject::SetSelectedState(
	bool bNewState)
{
	bSelected = bNewState;

	UpdateVisualState();
}

void AArchSelectableObject::UpdateVisualState()
{
	if (!LabelText)
	{
		return;
	}

	LabelText->SetTextRenderColor(
		bSelected
		? FColor::Yellow
		: FColor::White);
}

#if WITH_EDITOR

void AArchSelectableObject::PostEditChangeProperty(
	FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(
		PropertyChangedEvent);

	const FName PropertyName =
		PropertyChangedEvent.Property
		? PropertyChangedEvent.Property->GetFName()
		: NAME_None;

	if (
		PropertyName ==
		GET_MEMBER_NAME_CHECKED(
			AArchSelectableObject,
			bSelected)
		)
	{
		UpdateVisualState();
	}

	if (
		PropertyName ==
		GET_MEMBER_NAME_CHECKED(
			AArchSelectableObject,
			ArchObjectInfo)
		)
	{
		UpdateLabel();
	}
}

#endif

void AArchSelectableObject::SelectThisObject()
{
	UE_LOG(
		LogTemp,
		Warning,
		TEXT("Selected %s"),
		*ArchObjectInfo.ObjectID.ToString());
}

void AArchSelectableObject::OnObjectSelected_Implementation(const FArchObjectInfo& ObjectInfo)
{
	FString FormattedText = "";
	if (ObjectInfoComponent)
	{
		FormattedText = ObjectInfoComponent->GetFormattedObjectInfo();
	}
	else
	{
		FormattedText = UBPL_ArchVizUtilities::FormatObjectInfo(ObjectInfo);
	}
	
	ARCHVIZ_LOG(TEXT("Selection Event Triggered (Component):\n%s"), *FormattedText);
}