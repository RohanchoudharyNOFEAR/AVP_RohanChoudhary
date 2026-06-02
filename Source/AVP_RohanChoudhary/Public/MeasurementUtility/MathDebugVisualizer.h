// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MathDebugVisualizer.generated.h"

class USceneComponent;
class USplineComponent;
class UStaticMeshComponent;

class AArchObjectManager;

UCLASS()
class AVP_ROHANCHOUDHARY_API AMathDebugVisualizer : public AActor
{
	GENERATED_BODY()
	
public:

	AMathDebugVisualizer();
	UFUNCTION(BlueprintCallable)
	void ToggleDebugMode();

protected:

	virtual void BeginPlay() override;

	virtual void Tick(
		float DeltaTime) override;

public:

	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Components")
	USceneComponent* Root;

	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Components")
	USplineComponent* Spline;

	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Components")
	UStaticMeshComponent* SineMarker;

	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Components")
	UStaticMeshComponent* SplineMarker;

protected:

	UPROPERTY(
		EditAnywhere,
		Category = "Debug")
	bool bDebugEnabled = true;

	UPROPERTY(
		EditAnywhere,
		Category = "Debug")
	float SineAmplitude = 100.f;

	UPROPERTY(
		EditAnywhere,
		Category = "Debug")
	float SineSpeed = 2.f;

	UPROPERTY(
		EditAnywhere,
		Category = "Debug")
	float SplineSpeed = 300.f;

private:

	UPROPERTY()
	AArchObjectManager* CachedManager = nullptr;

	FVector SineStartLocation;

	float RunningTime = 0.f;

	float CurrentSplineDistance = 0.f;

private:

	void UpdateSineMarker(
		float DeltaTime);

	void UpdateSplineMarker(
		float DeltaTime);

	void DrawMathDebug();

	AArchObjectManager* FindManager();

	

	
};
