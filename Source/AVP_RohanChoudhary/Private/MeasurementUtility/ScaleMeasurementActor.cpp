// Fill out your copyright notice in the Description page of Project Settings.


#include "MeasurementUtility/ScaleMeasurementActor.h"
#include "MeasurementUtility/ScaleUtilitiesLibrary.h"
#include "Components/BillboardComponent.h"
#include "Components/SplineComponent.h"
#include "Components/WidgetComponent.h"

AScaleMeasurementActor::AScaleMeasurementActor()
{
	Root = CreateDefaultSubobject<USceneComponent>(
		TEXT("Root"));

	RootComponent = Root;

	StartPoint = CreateDefaultSubobject<UBillboardComponent>(
		TEXT("StartPoint"));

	StartPoint->SetupAttachment(Root);

	EndPoint = CreateDefaultSubobject<UBillboardComponent>(
		TEXT("EndPoint"));

	EndPoint->SetupAttachment(Root);

	MeasurementWidget =
		CreateDefaultSubobject<UWidgetComponent>(
			TEXT("MeasurementWidget"));

	MeasurementWidget->SetupAttachment(Root);

	MeasurementSpline =
		CreateDefaultSubobject<USplineComponent>(
			TEXT("MeasurementSpline"));

	MeasurementSpline->SetupAttachment(Root);
}

void AScaleMeasurementActor::OnConstruction(
	const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	UpdateMeasurement();
}

void AScaleMeasurementActor::UpdateMeasurement()
{
	const FVector StartLocation =
		StartPoint->GetComponentLocation();

	const FVector EndLocation =
		EndPoint->GetComponentLocation();

	const float DistanceCM =
		FVector::Distance(
			StartLocation,
			EndLocation);

	MeasurementData.Centimeters =
		DistanceCM;

	MeasurementData.Meters =
		UScaleUtilitiesLibrary::CentimetersToMeters(
			DistanceCM);

	MeasurementData.Millimeters =
		UScaleUtilitiesLibrary::CentimetersToMillimeters(
			DistanceCM);

	const FVector MidPoint =
		(StartLocation + EndLocation) * 0.5f;

	MeasurementWidget->SetWorldLocation(
		MidPoint +
		FVector(0.f, 0.f, WidgetOffsetZ));

	MeasurementSpline->ClearSplinePoints();

	MeasurementSpline->AddSplinePoint(
		StartLocation,
		ESplineCoordinateSpace::World);

	MeasurementSpline->AddSplinePoint(
		EndLocation,
		ESplineCoordinateSpace::World);

	MeasurementSpline->UpdateSpline();
}

FString AScaleMeasurementActor::GetFormattedMeasurementText() const
{
	return FString::Printf(
		TEXT("%s\n%.1f cm\n%.2f m\n%.1f mm"),
		*Label,
		MeasurementData.Centimeters,
		MeasurementData.Meters,
		MeasurementData.Millimeters);
}

