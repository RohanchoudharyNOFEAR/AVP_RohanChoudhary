// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/ArchObjectTypes.h"
#include "ArchObjectInfoComponent.generated.h"

/**
 * Reusable metadata component for selectable architectural objects
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AVP_ROHANCHOUDHARY_API UArchObjectInfoComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UArchObjectInfoComponent();

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ArchViz")
	FName ObjectID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ArchViz")
	FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ArchViz")
	EArchObjectCategory Category = EArchObjectCategory::Furniture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ArchViz")
	FName RoomName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ArchViz")
	float Area = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ArchViz", meta = (MultiLine = true))
	FString Notes;

public:

	/** Formats the component's metadata properties into a clean display string */
	UFUNCTION(BlueprintCallable, Category = "ArchViz")
	FString GetFormattedObjectInfo() const;
		
};
