// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Data/ArchObjectTypes.h"
#include "BPL_ArchVizUtilities.generated.h"

// Consistent debug printing macro: logs to Output Log and prints on screen in yellow
#define ARCHVIZ_LOG(Format, ...) \
	UE_LOG(LogTemp, Warning, Format, ##__VA_ARGS__); \
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(Format, ##__VA_ARGS__));

/**
 * Utility library for ArchViz visualizer
 */
UCLASS()
class AVP_ROHANCHOUDHARY_API UBPL_ArchVizUtilities : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	/** Formats FArchObjectInfo fields into a readable multiline display text */
	UFUNCTION(BlueprintPure, Category = "ArchViz")
	static FString FormatObjectInfo(const FArchObjectInfo& ObjectInfo);

	/** Exposes the consistent ARCHVIZ_LOG debug macro to Blueprints */
	UFUNCTION(BlueprintCallable, Category = "ArchViz")
	static void PrintDebugMessage(const FString& Message);

	UFUNCTION(BlueprintCallable, Category = "ArchViz")
	static bool ExportReviewNoteToCSV(const FString& ObjectID, const FString& DisplayName, const FString& RoomName, const FString& Note, FString& OutMessage);
	
};
