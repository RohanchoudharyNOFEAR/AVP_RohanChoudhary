// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Data/ArchObjectTypes.h"
#include "ArchSelectableObject.h"
#include "TypePracticeDisplay.generated.h"

class UTextRenderComponent;

/**
 * Technical Note: Why FText is better for user-facing UI text than FString:
 * 1. Localization: FText natively supports namespace key/value translations for multi-language projects.
 *    FString is a raw character array that cannot be localized automatically.
 * 2. Culture-Aware Formatting: FText handles gender rules, plural forms, and local number/date formatting
 *    correctly using FText::Format according to the active locale settings.
 * 3. Performance: FText employs a copy-on-write reference-counted implementation pointing to shared string tables,
 *    making copy and binding operations more efficient than duplicating raw FString char buffers.
 */

UCLASS()
class AVP_ROHANCHOUDHARY_API ATypePracticeDisplay : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATypePracticeDisplay();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UTextRenderComponent* DebugText;

	// Demonstrating FName: Unique identifier for the selected object
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TypePractice")
	FName SelectedObjectID;

	// Demonstrating FText: Localized user-facing UI display name
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TypePractice")
	FText SelectedDisplayName;

	// Demonstrating FVector: 3D location of the selected object
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TypePractice")
	FVector SelectedLocation;

	// Demonstrating FRotator: 3D rotation of the selected object
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TypePractice")
	FRotator SelectedRotation;

	// Demonstrating enum: Category classification
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TypePractice")
	EArchObjectCategory SelectedCategory;

	// Demonstrating FString: Non-localized internal notes / system debugging text
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TypePractice")
	FString SelectedNotes;

	// Demonstrating TArray: Dynamic array of all selectable objects in the showroom
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TypePractice")
	TArray<AArchSelectableObject*> AllSelectableObjects;

	// Demonstrating TMap: Fast key-to-value map linking ObjectID (FName) to its FArchObjectInfo struct
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TypePractice")
	TMap<FName, FArchObjectInfo> ObjectInfoDatabase;

public:

	/** Re-scans the level to populate lists and maps, and updates the display panel */
	UFUNCTION(CallInEditor, BlueprintCallable, Category = "TypePractice")
	void RefreshDisplay();

private:

	/** Event handler for manager selection callbacks */
	void HandleObjectSelected(const FArchObjectInfo& ObjectInfo);

	/** Re-formats and redraws the text visualizer in the level */
	void UpdateDisplayText();

};
