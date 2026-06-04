// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Data/ArchObjectTypes.h"
#include "ArchObjectManager.generated.h"

class AArchSelectableObject;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnArchObjectSelected, const FArchObjectInfo&);
UCLASS()
class AVP_ROHANCHOUDHARY_API AArchObjectManager : public AActor
{
	GENERATED_BODY()
	
public:

	AArchObjectManager();

	UFUNCTION(BlueprintCallable)
	void SelectObject(
		AArchSelectableObject* NewSelection);

	UFUNCTION(BlueprintCallable)
	AArchSelectableObject* GetCurrentSelection() const;

	UFUNCTION(BlueprintCallable, Category = "ArchViz")
	void ToggleObjectIDs();

	UFUNCTION(BlueprintPure, Category = "ArchViz")
	bool IsShowingObjectIDs() const { return bShowObjectIDs; }

	UFUNCTION(BlueprintCallable, Category = "ArchViz")
	bool GetMetadataForObject(FName ObjectID, FArchObjectCSVRow& OutRow) const;

	FOnArchObjectSelected OnObjectSelected;

protected:

	virtual void BeginPlay() override;

private:

	void BuildObjectDatabase();

public:

	UPROPERTY(
		BlueprintReadOnly,
		Category = "ArchViz")
	TArray<FName> ObjectNames;

	UPROPERTY(
		BlueprintReadOnly,
		Category = "ArchViz")
	TMap<FName, FText> ObjectDisplayNames;

	UPROPERTY(
		BlueprintReadOnly,
		Category = "ArchViz")
	TSet<FName> SelectedObjectIDs;

protected:
	UPROPERTY(BlueprintReadOnly)
	AArchSelectableObject* CurrentSelection = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ArchViz")
	bool bShowObjectIDs = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ArchViz")
	class UDataTable* ArchObjectDataTable = nullptr;

};
