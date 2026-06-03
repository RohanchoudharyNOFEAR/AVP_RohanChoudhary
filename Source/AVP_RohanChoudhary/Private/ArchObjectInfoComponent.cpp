// Fill out your copyright notice in the Description page of Project Settings.


#include "ArchObjectInfoComponent.h"

// Sets default values for this component's properties
UArchObjectInfoComponent::UArchObjectInfoComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

FString UArchObjectInfoComponent::GetFormattedObjectInfo() const
{
	FString CategoryStr = UEnum::GetDisplayValueAsText(Category).ToString();
	
	return FString::Printf(
		TEXT("Object ID: %s\nName: %s\nCategory: %s\nRoom: %s\nArea: %.2f sq m\nNotes: %s"),
		*ObjectID.ToString(),
		*DisplayName.ToString(),
		*CategoryStr,
		*RoomName.ToString(),
		Area,
		*Notes
	);
}
