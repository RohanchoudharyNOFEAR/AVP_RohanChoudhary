// Fill out your copyright notice in the Description page of Project Settings.


#include "MeasurementUtility/ScaleUtilitiesLibrary.h"

float UScaleUtilitiesLibrary::MetersToCentimeters(float Meters)
{
    return Meters * 100.f;
}

float UScaleUtilitiesLibrary::CentimetersToMeters(float Centimeters)
{
    return Centimeters / 100.f;
}

float UScaleUtilitiesLibrary::MillimetersToCentimeters(float Millimeters)
{
    return Millimeters / 10.f;
}

float UScaleUtilitiesLibrary::CentimetersToMillimeters(float Centimeters)
{
    return Centimeters * 10.f;
}