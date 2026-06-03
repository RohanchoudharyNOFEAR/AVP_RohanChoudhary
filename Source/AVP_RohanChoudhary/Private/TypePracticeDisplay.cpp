// Fill out your copyright notice in the Description page of Project Settings.


#include "TypePracticeDisplay.h"
#include "Components/TextRenderComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ArchObjectManager.h"
#include "ArchObjectInfoComponent.h"
#include "BPL_ArchVizUtilities.h"

// Sets default values
ATypePracticeDisplay::ATypePracticeDisplay()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	DebugText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("DebugText"));
	DebugText->SetupAttachment(Root);
	DebugText->SetRelativeLocation(FVector(0.f, 0.f, 100.f));
	DebugText->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
	DebugText->SetWorldSize(24.f);
	DebugText->SetTextRenderColor(FColor::Cyan);

	SelectedCategory = EArchObjectCategory::Furniture;
}

// Called when the game starts or when spawned
void ATypePracticeDisplay::BeginPlay()
{
	Super::BeginPlay();
	
	// Bind to the Selection Manager's native selection delegate
	TArray<AActor*> FoundManagers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AArchObjectManager::StaticClass(), FoundManagers);
	
	if (FoundManagers.Num() > 0)
	{
		if (AArchObjectManager* Manager = Cast<AArchObjectManager>(FoundManagers[0]))
		{
			Manager->OnObjectSelected.AddUObject(this, &ATypePracticeDisplay::HandleObjectSelected);
		}
	}

	RefreshDisplay();
}

void ATypePracticeDisplay::RefreshDisplay()
{
	AllSelectableObjects.Empty();
	ObjectInfoDatabase.Empty();

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AArchSelectableObject::StaticClass(), FoundActors);

	for (AActor* Actor : FoundActors)
	{
		if (AArchSelectableObject* Selectable = Cast<AArchSelectableObject>(Actor))
		{
			AllSelectableObjects.Add(Selectable);
			ObjectInfoDatabase.Add(Selectable->GetObjectInfo().ObjectID, Selectable->GetObjectInfo());
		}
	}

	UpdateDisplayText();
}

void ATypePracticeDisplay::HandleObjectSelected(const FArchObjectInfo& ObjectInfo)
{
	AArchSelectableObject* SelectedActor = nullptr;

	for (AArchSelectableObject* Selectable : AllSelectableObjects)
	{
		if (Selectable && Selectable->GetObjectInfo().ObjectID == ObjectInfo.ObjectID)
		{
			SelectedActor = Selectable;
			break;
		}
	}

	if (SelectedActor)
	{
		SelectedObjectID = ObjectInfo.ObjectID;
		SelectedDisplayName = ObjectInfo.DisplayName;
		SelectedLocation = SelectedActor->GetActorLocation();
		SelectedRotation = SelectedActor->GetActorRotation();
		SelectedCategory = ObjectInfo.Category;

		if (SelectedActor->ObjectInfoComponent)
		{
			SelectedNotes = SelectedActor->ObjectInfoComponent->Notes;
		}
		else
		{
			SelectedNotes = TEXT("No Component Attached");
		}
	}

	UpdateDisplayText();
}

void ATypePracticeDisplay::UpdateDisplayText()
{
	if (!DebugText) return;

	FString CategoryStr = UEnum::GetDisplayValueAsText(SelectedCategory).ToString();
	FString DisplayStr = FString::Printf(
		TEXT("=== ARCHVIZ DEBUG PANEL ===\n")
		TEXT("Selected ID: %s\n")
		TEXT("Display Name: %s\n")
		TEXT("Location: X=%.1f Y=%.1f Z=%.1f\n")
		TEXT("Rotation: P=%.1f Y=%.1f R=%.1f\n")
		TEXT("Category: %s\n")
		TEXT("Notes: %s\n")
		TEXT("---------------------------\n")
		TEXT("Total Registered Objects: %d"),
		*SelectedObjectID.ToString(),
		*SelectedDisplayName.ToString(),
		SelectedLocation.X, SelectedLocation.Y, SelectedLocation.Z,
		SelectedRotation.Pitch, SelectedRotation.Yaw, SelectedRotation.Roll,
		*CategoryStr,
		*SelectedNotes,
		AllSelectableObjects.Num()
	);

	DebugText->SetText(FText::FromString(DisplayStr));
}
