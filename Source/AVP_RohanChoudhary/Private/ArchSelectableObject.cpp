// Fill out your copyright notice in the Description page of Project Settings.


#include "ArchSelectableObject.h"

#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"

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
}

void AArchSelectableObject::OnConstruction(
	const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	UpdateLabel();
}

void AArchSelectableObject::UpdateLabel()
{
	const FString LabelString =
		FString::Printf(
			TEXT("%s\n%s"),
			*ArchObjectInfo.ObjectID.ToString(),
			*ArchObjectInfo.DisplayName.ToString());

	LabelText->SetText(
		FText::FromString(LabelString));
}

FArchObjectInfo
AArchSelectableObject::GetObjectInfo() const
{
	return ArchObjectInfo;
}

void AArchSelectableObject::SetHighlightState(
	bool bNewState)
{
	bHighlighted = bNewState;

	if (bHighlighted)
	{
		LabelText->SetTextRenderColor(
			FColor::Green);
	}
	else
	{
		LabelText->SetTextRenderColor(
			FColor::White);
	}
}

void AArchSelectableObject::SetSelectedState(
	bool bNewState)
{
	bSelected = bNewState;

	if (bSelected)
	{
		LabelText->SetTextRenderColor(
			FColor::Yellow);
	}
	else
	{
		LabelText->SetTextRenderColor(
			FColor::White);
	}
}