// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ArchSelectableObject.h"
#include "ArchAnimatedDoor.generated.h"

class UStaticMeshComponent;
class UWidgetComponent;

/**
 * An interactive architectural door component that slides up and down driven by a Timeline.
 */
UCLASS()
class AVP_ROHANCHOUDHARY_API AArchAnimatedDoor : public AArchSelectableObject
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AArchAnimatedDoor();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> DefaultSceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> FrameMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> DoorMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UWidgetComponent> StateWidgetComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DoorSettings")
	FVector ClosedLocalLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DoorSettings")
	FVector OpenedLocalLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "DoorSettings")
	bool bIsDoorOpen = false;

public:
	// Toggles the target state of the door and triggers OnToggleDoor event
	UFUNCTION(BlueprintCallable, Category = "DoorSettings")
	void ToggleDoor();

	// Updates the relative height location of the door based on Timeline interpolation value
	UFUNCTION(BlueprintCallable, Category = "DoorSettings")
	void UpdateDoorHeight(float InterpolationValue);

	// Event triggered to run the Timeline animation in Blueprints
	UFUNCTION(BlueprintImplementableEvent, Category = "DoorSettings")
	void OnToggleDoor();
};
