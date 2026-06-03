// Fill out your copyright notice in the Description page of Project Settings.


#include "BPL_ArchVizUtilities.h"

FString UBPL_ArchVizUtilities::FormatObjectInfo(const FArchObjectInfo& ObjectInfo)
{
	FString CategoryStr = UEnum::GetDisplayValueAsText(ObjectInfo.Category).ToString();
	
	return FString::Printf(
		TEXT("Object ID: %s\nName: %s\nCategory: %s\nRoom: %s\nMaterial Group: %s"),
		*ObjectInfo.ObjectID.ToString(),
		*ObjectInfo.DisplayName.ToString(),
		*CategoryStr,
		*ObjectInfo.RoomName.ToString(),
		*ObjectInfo.MaterialGroup.ToString()
	);
}

void UBPL_ArchVizUtilities::PrintDebugMessage(const FString& Message)
{
	ARCHVIZ_LOG(TEXT("%s"), *Message);
}
