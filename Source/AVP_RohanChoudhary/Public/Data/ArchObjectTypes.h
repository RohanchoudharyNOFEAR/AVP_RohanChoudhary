#pragma once

#include "CoreMinimal.h"
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