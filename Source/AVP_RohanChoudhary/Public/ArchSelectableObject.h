// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Data/ArchObjectTypes.h"
#include "ArchSelectableObject.generated.h"


class UStaticMeshComponent;
class UTextRenderComponent;
class UArchObjectInfoComponent;
UCLASS()
class AVP_ROHANCHOUDHARY_API AArchSelectableObject : public AActor
{
	GENERATED_BODY()
	
public:

	AArchSelectableObject();

	UFUNCTION(CallInEditor)
	void SelectThisObject();
protected:

	virtual void OnConstruction(
		const FTransform& Transform) override;

#if WITH_EDITOR

	virtual void PostEditChangeProperty(
		FPropertyChangedEvent& PropertyChangedEvent) override;

#endif

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
		VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Components",
		meta = (AllowPrivateAccess = "true"))
	UArchObjectInfoComponent* ObjectInfoComponent;

	UPROPERTY(
		EditAnywhere,
		BlueprintReadWrite,
		Category = "ArchViz")
	FArchObjectInfo ArchObjectInfo;

	UPROPERTY(
		EditInstanceOnly,
		BlueprintReadWrite,
		Category = "ArchViz")
	bool bSelected = false;

	

	UFUNCTION(
		BlueprintCallable,
		Category = "ArchViz")
	FArchObjectInfo GetObjectInfo() const;


	UFUNCTION(
		BlueprintCallable,
		Category = "ArchViz")
	void SetSelectedState(
		bool bNewState);

	UFUNCTION(BlueprintNativeEvent, Category = "ArchViz")
	void OnObjectSelected(const FArchObjectInfo& ObjectInfo);

	void UpdateLabel();

private:

	void UpdateVisualState();
};
