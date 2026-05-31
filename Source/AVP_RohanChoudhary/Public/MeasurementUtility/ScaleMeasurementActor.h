// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ScaleMeasurementActor.generated.h"

class UBillboardComponent;
class UWidgetComponent;
class USplineComponent;

USTRUCT(BlueprintType)
struct FMeasurementData
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    float Centimeters = 0.f;

    UPROPERTY(BlueprintReadOnly)
    float Meters = 0.f;

    UPROPERTY(BlueprintReadOnly)
    float Millimeters = 0.f;
};

UCLASS()
class AVP_ROHANCHOUDHARY_API AScaleMeasurementActor : public AActor
{
	GENERATED_BODY()
	
public:

    AScaleMeasurementActor();

protected:

    virtual void OnConstruction(const FTransform& Transform) override;

public:

    UPROPERTY(VisibleAnywhere)
    USceneComponent* Root;

    UPROPERTY(VisibleAnywhere)
    UBillboardComponent* StartPoint;

    UPROPERTY(VisibleAnywhere)
    UBillboardComponent* EndPoint;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UWidgetComponent* MeasurementWidget;

    UPROPERTY(VisibleAnywhere)
    USplineComponent* MeasurementSpline;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Measurement")
    FString Label = TEXT("Measurement");

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Measurement")
    float WidgetOffsetZ = 50.f;

    UPROPERTY(BlueprintReadOnly, Category = "Measurement")
    FMeasurementData MeasurementData;

    UFUNCTION(BlueprintCallable, Category = "Measurement")
    void UpdateMeasurement();

    UFUNCTION(BlueprintPure, Category = "Measurement")
    FString GetFormattedMeasurementText() const;
};
