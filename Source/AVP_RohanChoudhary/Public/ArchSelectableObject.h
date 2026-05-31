// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Data/ArchObjectTypes.h"
#include "ArchSelectableObject.generated.h"


class UStaticMeshComponent;
class UTextRenderComponent;
UCLASS()
class AVP_ROHANCHOUDHARY_API AArchSelectableObject : public AActor
{
	GENERATED_BODY()
	
public:

	AArchSelectableObject();

protected:

	virtual void OnConstruction(
		const FTransform& Transform) override;

public:

	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Components")
	USceneComponent* Root;

	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Components")
	UStaticMeshComponent* Mesh;

	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Components")
	UTextRenderComponent* LabelText;

	UPROPERTY(
		EditAnywhere,
		BlueprintReadWrite,
		Category = "ArchViz")
	FArchObjectInfo ArchObjectInfo;

	UPROPERTY(
		BlueprintReadOnly,
		Category = "ArchViz")
	bool bSelected = false;

	UPROPERTY(
		BlueprintReadOnly,
		Category = "ArchViz")
	bool bHighlighted = false;

	UFUNCTION(
		BlueprintCallable,
		Category = "ArchViz")
	FArchObjectInfo GetObjectInfo() const;

	UFUNCTION(
		BlueprintCallable,
		Category = "ArchViz")
	void SetHighlightState(
		bool bNewState);

	UFUNCTION(
		BlueprintCallable,
		Category = "ArchViz")
	void SetSelectedState(
		bool bNewState);

private:

	void UpdateLabel();
};
