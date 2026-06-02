// Fill out your copyright notice in the Description page of Project Settings.


#include "MeasurementUtility/MathDebugVisualizer.h"

#include "Components/SceneComponent.h"
#include "Components/SplineComponent.h"
#include "Components/StaticMeshComponent.h"

#include "ArchObjectManager.h"

#include "EngineUtils.h"

// Sets default values
AMathDebugVisualizer::AMathDebugVisualizer()
{
	PrimaryActorTick.bCanEverTick = true;

	Root =
		CreateDefaultSubobject<USceneComponent>(
			TEXT("Root"));

	RootComponent = Root;

	Spline =
		CreateDefaultSubobject<USplineComponent>(
			TEXT("Spline"));

	Spline->SetupAttachment(Root);

	SineMarker =
		CreateDefaultSubobject<UStaticMeshComponent>(
			TEXT("SineMarker"));

	SineMarker->SetupAttachment(Root);

	SplineMarker =
		CreateDefaultSubobject<UStaticMeshComponent>(
			TEXT("SplineMarker"));

	SplineMarker->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AMathDebugVisualizer::BeginPlay()
{
	Super::BeginPlay();
	
	SineStartLocation =
		SineMarker->GetComponentLocation();

	CachedManager = FindManager();
}

// Called every frame
void AMathDebugVisualizer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Super::Tick(DeltaTime);

	if (!bDebugEnabled)
	{
		return;
	}

	UpdateSineMarker(
		DeltaTime);

	UpdateSplineMarker(
		DeltaTime);

}

AArchObjectManager*
AMathDebugVisualizer::FindManager()
{
	for (TActorIterator<AArchObjectManager> It(GetWorld()); It; ++It)
	{
		return *It;
	}

	return nullptr;
}

void AMathDebugVisualizer::UpdateSineMarker(
	float DeltaTime)
{
	RunningTime += DeltaTime;

	const float ZOffset =
		FMath::Sin(
			RunningTime * SineSpeed)
		* SineAmplitude;

	FVector NewLocation =
		SineStartLocation;

	NewLocation.Z += ZOffset;

	SineMarker->SetWorldLocation(
		NewLocation);
}

void AMathDebugVisualizer::UpdateSplineMarker(
	float DeltaTime)
{
	if (!Spline)
	{
		return;
	}

	const float SplineLength =
		Spline->GetSplineLength();

	if (SplineLength <= 0.f)
	{
		return;
	}

	CurrentSplineDistance +=
		SplineSpeed * DeltaTime;

	if (CurrentSplineDistance >
		SplineLength)
	{
		CurrentSplineDistance = 0.f;
	}

	const FVector NewLocation =
		Spline->GetLocationAtDistanceAlongSpline(
			CurrentSplineDistance,
			ESplineCoordinateSpace::World);

	SplineMarker->SetWorldLocation(
		NewLocation);
}