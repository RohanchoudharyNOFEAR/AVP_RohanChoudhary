// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ScaleUtilitiesLibrary.generated.h"

/**
 * 
 */
UCLASS()
class AVP_ROHANCHOUDHARY_API UScaleUtilitiesLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

    UFUNCTION(BlueprintPure, Category = "Scale")
    static float MetersToCentimeters(float Meters);

    UFUNCTION(BlueprintPure, Category = "Scale")
    static float CentimetersToMeters(float Centimeters);

    UFUNCTION(BlueprintPure, Category = "Scale")
    static float MillimetersToCentimeters(float Millimeters);

    UFUNCTION(BlueprintPure, Category = "Scale")
    static float CentimetersToMillimeters(float Centimeters);
};
