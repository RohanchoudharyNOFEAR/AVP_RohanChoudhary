// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Data/ArchObjectTypes.h"
#include "AVP_RohanChoudharyPlayerController.generated.h"

class UInputMappingContext;
class UUserWidget;
class UInputAction;
class AArchObjectManager;
class AArchSelectableObject;
class UDataLayerAsset;

/**
 *  Basic PlayerController class for a third person game
 *  Manages input mappings
 */
UCLASS(abstract)
class AAVP_RohanChoudharyPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:

	/** Input Mapping Contexts */
	UPROPERTY(EditAnywhere, Category = "Input|Input Mappings")
	TArray<UInputMappingContext*> DefaultMappingContexts;

	/** Input Mapping Contexts */
	UPROPERTY(EditAnywhere, Category = "Input|Input Mappings")
	TArray<UInputMappingContext*> MobileExcludedMappingContexts;

	/** Mobile controls widget to spawn */
	UPROPERTY(EditAnywhere, Category = "Input|Touch Controls")
	TSubclassOf<UUserWidget> MobileControlsWidgetClass;

	/** Pointer to the mobile controls widget */
	UPROPERTY()
	TObjectPtr<UUserWidget> MobileControlsWidget;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> ReviewNotesWidgetClass;

	UPROPERTY()
	UUserWidget* ReviewNotesWidget = nullptr;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> ObjectInfoPanelWidgetClass;

	UPROPERTY()
	UUserWidget* ObjectInfoPanelWidget = nullptr;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> ControlsOverlayWidgetClass;

	UPROPERTY()
	UUserWidget* ControlsOverlayWidget = nullptr;

	/** If true, the player will use UMG touch controls even if not playing on mobile platforms */
	UPROPERTY(EditAnywhere, Config, Category = "Input|Touch Controls")
	bool bForceTouchControls = false;

public:
	void ShowInputDebugMessage(const FString& ActionName);

	void ToggleControlsOverlay();

	UFUNCTION(BlueprintCallable, Category = "DataLayers")
	void HandleToggleFurniture();

	virtual void Tick(float DeltaTime) override;

protected:
	/** Gameplay initialization */
	virtual void BeginPlay() override;

	/** Input mapping context setup */
	virtual void SetupInputComponent() override;

	/** Returns true if the player should use UMG touch controls */
	bool ShouldUseTouchControls() const;

	UPROPERTY(EditAnywhere, Category = "Input|Actions")
	TObjectPtr<UInputAction> SelectAction;

	UPROPERTY(EditAnywhere, Category = "Input|Actions")
	TObjectPtr < UInputAction> ToggleMathDebugAction;

	UPROPERTY(EditAnywhere, Category = "Input|Actions")
	TObjectPtr<UInputAction> ToggleObjectIDsAction;

	UPROPERTY(EditAnywhere, Category = "Input|Actions")
	TObjectPtr<UInputAction> RefreshDebugAction;

	UPROPERTY(EditAnywhere, Category = "Input|Actions")
	TObjectPtr<UInputAction> BackAction;

	UPROPERTY(EditAnywhere, Category = "Input|Actions")
	TObjectPtr<UInputAction> ToggleFurnitureAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataLayers")
	TObjectPtr<UDataLayerAsset> FurnitureDataLayerAsset;

private:

	UPROPERTY()
	TObjectPtr<AArchObjectManager> CachedManager;

	UPROPERTY(Transient)
	AArchSelectableObject* CurrentHoveredObject = nullptr;

	void HandleToggleMathDebug();

	void HandleToggleObjectIDs();

	void HandleRefreshDebug();

	void HandleSaveTempNote();

	void SetNavigationMode(bool bCursorActive);

	void HandleObjectSelectedStateChanged(const FArchObjectInfo& ObjectInfo);

private:

	void HandleSelectPressed();

	void HandleBackPressed();

	AArchObjectManager* FindManager();

};
