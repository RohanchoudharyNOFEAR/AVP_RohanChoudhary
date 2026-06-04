// Fill out your copyright notice in the Description page of Project Settings.


#include "BPL_ArchVizUtilities.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "HAL/PlatformFileManager.h"
#include "Misc/DateTime.h"

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

static FString EscapeCSVField(const FString& Field)
{
	if (Field.Contains(TEXT(",")) || Field.Contains(TEXT("\"")) || Field.Contains(TEXT("\n")) || Field.Contains(TEXT("\r")))
	{
		FString Escaped = Field.Replace(TEXT("\""), TEXT("\"\""));
		return FString::Printf(TEXT("\"%s\""), *Escaped);
	}
	return Field;
}

bool UBPL_ArchVizUtilities::ExportReviewNoteToCSV(const FString& ObjectID, const FString& DisplayName, const FString& RoomName, const FString& Note, FString& OutMessage)
{
	FString FilePath = FPaths::Combine(FPaths::ProjectDir(), TEXT("ReviewNotes.csv"));
	
	FString RowData = "";
	if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*FilePath))
	{
		RowData += TEXT("Timestamp,ObjectID,DisplayName,RoomName,Note\n");
	}
	
	FString Timestamp = FDateTime::Now().ToString(TEXT("%Y-%m-%d %H:%M:%S"));
	
	FString EscapedTimestamp = EscapeCSVField(Timestamp);
	FString EscapedObjectID = EscapeCSVField(ObjectID);
	FString EscapedDisplayName = EscapeCSVField(DisplayName);
	FString EscapedRoomName = EscapeCSVField(RoomName);
	FString EscapedNote = EscapeCSVField(Note);
	
	RowData += FString::Printf(TEXT("%s,%s,%s,%s,%s\n"),
		*EscapedTimestamp,
		*EscapedObjectID,
		*EscapedDisplayName,
		*EscapedRoomName,
		*EscapedNote);
		
	if (FFileHelper::SaveStringToFile(RowData, *FilePath, FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM, &IFileManager::Get(), FILEWRITE_Append))
	{
		OutMessage = FString::Printf(TEXT("Successfully saved review note to %s"), *FilePath);
		return true;
	}
	else
	{
		OutMessage = TEXT("Failed to write to ReviewNotes.csv");
		return false;
	}
}
