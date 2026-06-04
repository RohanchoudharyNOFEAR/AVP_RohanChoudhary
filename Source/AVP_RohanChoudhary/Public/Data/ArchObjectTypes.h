#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ArchObjectTypes.generated.h"

UENUM(BlueprintType)
enum class EArchObjectCategory : uint8
{
	Door		UMETA(DisplayName = "Door"),
	Furniture	UMETA(DisplayName = "Furniture"),
	Glass		UMETA(DisplayName = "Glass"),
	Wall		UMETA(DisplayName = "Wall"),
	Fixture		UMETA(DisplayName = "Fixture"),
	Display		UMETA(DisplayName = "Display")
};

USTRUCT(BlueprintType)
struct FArchObjectInfo
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName ObjectID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EArchObjectCategory Category =
		EArchObjectCategory::Furniture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName RoomName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName MaterialGroup;
};

USTRUCT(BlueprintType)
struct FArchObjectCSVRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ArchViz")
	FName ObjectID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ArchViz")
	FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ArchViz")
	EArchObjectCategory Category = EArchObjectCategory::Furniture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ArchViz")
	FName RoomName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ArchViz")
	float AreaSqM = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ArchViz")
	FName MaterialGroup;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ArchViz")
	FString Description;
};