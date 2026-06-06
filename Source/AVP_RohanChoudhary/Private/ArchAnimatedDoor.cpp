// Fill out your copyright notice in the Description page of Project Settings.


#include "ArchAnimatedDoor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"

// Sets default values
AArchAnimatedDoor::AArchAnimatedDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;

	FrameMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrameMesh"));
	FrameMesh->SetupAttachment(RootComponent);

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	DoorMesh->SetupAttachment(FrameMesh);

	StateWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("StateWidgetComponent"));
	StateWidgetComponent->SetupAttachment(FrameMesh);
	StateWidgetComponent->SetWidgetSpace(EWidgetSpace::World);

	ClosedLocalLocation = FVector::ZeroVector;
	OpenedLocalLocation = FVector(0.f, 0.f, 300.f); // Default sliding up by 300 units
	bIsDoorOpen = false;
}

void AArchAnimatedDoor::ToggleDoor()
{
	bIsDoorOpen = !bIsDoorOpen;
	OnToggleDoor();
}

void AArchAnimatedDoor::UpdateDoorHeight(float InterpolationValue)
{
	if (DoorMesh)
	{
		FVector NewLoc = FMath::Lerp(ClosedLocalLocation, OpenedLocalLocation, InterpolationValue);
		DoorMesh->SetRelativeLocation(NewLoc);
	}
}
