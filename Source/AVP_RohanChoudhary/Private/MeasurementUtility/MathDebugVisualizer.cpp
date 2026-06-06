// Fill out your copyright notice in the Description page of Project Settings.


#include "MeasurementUtility/MathDebugVisualizer.h"

#include "Components/SceneComponent.h"
#include "Components/SplineComponent.h"
#include "Components/StaticMeshComponent.h"
#include "ArchSelectableObject.h"
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

	DrawMathDebug();

}

void AMathDebugVisualizer::DrawMathDebug()
{
	if (!CachedManager)
	{
		return;
	}

	AArchSelectableObject* Selected =
		CachedManager->GetCurrentSelection();

	if (!Selected)
	{
		return;
	}

	APlayerController* PC =
		GetWorld()->GetFirstPlayerController();

	if (!PC)
	{
		return;
	}

	FVector ViewLocation;
	FRotator ViewRotation;

	PC->GetPlayerViewPoint(
		ViewLocation,
		ViewRotation);

	const FVector Forward =
		ViewRotation.Vector();

	const FVector UP = ViewRotation.Vector().UpVector;

	DrawDebugLine(
		GetWorld(),
		ViewLocation,
		ViewLocation + Forward * 100.f + UP * -50,
		FColor::Green,
		false,
		0.f,
		0,
		3.f);

	const FVector ObjectLocation =
		Selected->GetActorLocation();

	const FVector DirectionToObject =
		(ObjectLocation - ViewLocation)
		.GetSafeNormal();

	const float Distance =
		FVector::Distance(
			ViewLocation,
			ObjectLocation);

	const float Dot =
		FVector::DotProduct(
			Forward,
			DirectionToObject);

	const FString FrontResult =
		Dot > 0.f
		? TEXT("IN FRONT")
		: TEXT("BEHIND");

	const FVector Cross =
		FVector::CrossProduct(
			Forward,
			DirectionToObject);

	const FString SideResult =
		Cross.Z > 0.f
		? TEXT("RIGHT")
		: TEXT("LEFT");

	FString DebugText;

	DebugText +=
		TEXT("Forward Vector\n");

	DebugText +=
		FString::Printf(
			TEXT("Distance: %.2f\n"),
			Distance);

	DebugText +=
		FString::Printf(
			TEXT("Dot Product: %.2f (%s)\n"),
			Dot,
			*FrontResult);

	DebugText +=
		FString::Printf(
			TEXT("Cross Product Z: %.2f (%s)\n"),
			Cross.Z,
			*SideResult);

	DebugText +=
		TEXT("Sin() Floating Marker\n");

	DebugText +=
		TEXT("Spline Path Marker");

	// Suppressed on-screen debug text as requested
	/*
	GEngine->AddOnScreenDebugMessage(
		100,
		0.f,
		FColor::Yellow,
		DebugText);
	*/
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

void AMathDebugVisualizer::ToggleDebugMode()
{
	bDebugEnabled = !bDebugEnabled;

	UE_LOG(
		LogTemp,
		Warning,
		TEXT("Math Debug: %s"),
		bDebugEnabled
		? TEXT("ON")
		: TEXT("OFF"));
}