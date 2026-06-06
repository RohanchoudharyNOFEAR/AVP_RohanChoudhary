// Copyright Epic Games, Inc. All Rights Reserved.


#include "AVP_RohanChoudharyPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"
#include "Blueprint/UserWidget.h"
#include "AVP_RohanChoudhary.h"
#include "Widgets/Input/SVirtualJoystick.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "MeasurementUtility/MathDebugVisualizer.h"
#include "ArchObjectManager.h"
#include "ArchSelectableObject.h"
#include "ArchAnimatedDoor.h"
#include "TypePracticeDisplay.h"
#include "BPL_ArchVizUtilities.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "WorldPartition/DataLayer/DataLayerSubsystem.h"
#include "WorldPartition/DataLayer/DataLayerAsset.h"
#include "WorldPartition/DataLayer/DataLayerInstance.h"

void AAVP_RohanChoudharyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	PrimaryActorTick.bCanEverTick = true;

	// only spawn touch controls on local player controllers
	if (ShouldUseTouchControls() && IsLocalPlayerController())
	{
		// spawn the mobile controls widget
		MobileControlsWidget = CreateWidget<UUserWidget>(this, MobileControlsWidgetClass);

		if (MobileControlsWidget)
		{
			// add the controls to the player screen
			MobileControlsWidget->AddToPlayerScreen(0);
		}
		else {
			UE_LOG(LogAVP_RohanChoudhary, Error, TEXT("Could not spawn mobile controls widget."));
		}
	}

	CachedManager = FindManager();

	if (CachedManager)
	{
		CachedManager->OnObjectSelected.AddUObject(this, &AAVP_RohanChoudharyPlayerController::HandleObjectSelectedStateChanged);
	}

	SetNavigationMode(false); // Start in free-look (no cursor)
}

void AAVP_RohanChoudharyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// only add IMCs for local player controllers
	if (IsLocalPlayerController())
	{
		// Add Input Mapping Contexts
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
			{
				Subsystem->AddMappingContext(CurrentContext, 0);
			}

			// only add these IMCs if we're not using mobile touch input
			if (!ShouldUseTouchControls())
			{
				for (UInputMappingContext* CurrentContext : MobileExcludedMappingContexts)
				{
					Subsystem->AddMappingContext(CurrentContext, 0);
				}
			}
		}
	}

	if (UEnhancedInputComponent* EnhancedInput =
		Cast<UEnhancedInputComponent>(InputComponent))
	{
		if (SelectAction)
		{
			EnhancedInput->BindAction(
				SelectAction,
				ETriggerEvent::Started,
				this,
				&AAVP_RohanChoudharyPlayerController::HandleSelectPressed);
		}

		if (ToggleMathDebugAction)
		{
			EnhancedInput->BindAction(
				ToggleMathDebugAction,
				ETriggerEvent::Started,
				this,
				&AAVP_RohanChoudharyPlayerController::HandleToggleMathDebug);
		}

		if (ToggleObjectIDsAction)
		{
			EnhancedInput->BindAction(
				ToggleObjectIDsAction,
				ETriggerEvent::Started,
				this,
				&AAVP_RohanChoudharyPlayerController::HandleToggleObjectIDs);
		}

		if (RefreshDebugAction)
		{
			EnhancedInput->BindAction(
				RefreshDebugAction,
				ETriggerEvent::Started,
				this,
				&AAVP_RohanChoudharyPlayerController::HandleRefreshDebug);
		}

		if (BackAction)
		{
			EnhancedInput->BindAction(
				BackAction,
				ETriggerEvent::Started,
				this,
				&AAVP_RohanChoudharyPlayerController::HandleBackPressed);
		}

		if (ToggleFurnitureAction)
		{
			EnhancedInput->BindAction(
				ToggleFurnitureAction,
				ETriggerEvent::Started,
				this,
				&AAVP_RohanChoudharyPlayerController::HandleToggleFurniture);
		}

		if (ToggleDoorAction)
		{
			EnhancedInput->BindAction(
				ToggleDoorAction,
				ETriggerEvent::Started,
				this,
				&AAVP_RohanChoudharyPlayerController::HandleToggleDoor);
		}
	}

	if (InputComponent)
	{
		InputComponent->BindKey(EKeys::N, IE_Pressed, this, &AAVP_RohanChoudharyPlayerController::HandleSaveTempNote);
		InputComponent->BindKey(EKeys::H, IE_Pressed, this, &AAVP_RohanChoudharyPlayerController::ToggleControlsOverlay);
	}
}

AArchObjectManager*
AAVP_RohanChoudharyPlayerController::FindManager()
{
	for (TActorIterator<AArchObjectManager> It(GetWorld()); It; ++It)
	{
		return *It;
	}

	return nullptr;
}

bool AAVP_RohanChoudharyPlayerController::ShouldUseTouchControls() const
{
	// are we on a mobile platform? Should we force touch?
	return SVirtualJoystick::ShouldDisplayTouchInterface() || bForceTouchControls;
}

void AAVP_RohanChoudharyPlayerController::HandleSelectPressed()
{
	UE_LOG(
		LogTemp,
		Warning,
		TEXT("select clicked"));

	FHitResult Hit;
	bool bHit = false;

	if (bShowMouseCursor)
	{
		bHit = GetHitResultUnderCursor(ECC_Visibility, false, Hit);
	}
	else
	{
		FVector CameraLocation;
		FRotator CameraRotation;
		GetPlayerViewPoint(CameraLocation, CameraRotation);
		FVector End = CameraLocation + (CameraRotation.Vector() * 10000.f);
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(GetPawn());
		bHit = GetWorld()->LineTraceSingleByChannel(Hit, CameraLocation, End, ECC_Visibility, QueryParams);
	}

	AArchSelectableObject* Object = nullptr;
	if (bHit && Hit.GetActor())
	{
		Object = Cast<AArchSelectableObject>(Hit.GetActor());
	}

	if (Object)
	{
		UE_LOG(
			LogTemp,
			Warning,
			TEXT("Hit Object: %s"),
			*Object->GetName());

		if (ObjectInfoPanelWidgetClass && !ObjectInfoPanelWidget)
		{
			ObjectInfoPanelWidget = CreateWidget<UUserWidget>(this, ObjectInfoPanelWidgetClass);
			if (ObjectInfoPanelWidget)
			{
				ObjectInfoPanelWidget->AddToViewport(10);
			}
		}
	}
	else
	{
		UE_LOG(
			LogTemp,
			Warning,
			TEXT("Hit Actor but NOT ArchSelectableObject"));
	}

	if (CachedManager)
	{
		CachedManager->SelectObject(Object);
	}
}

void AAVP_RohanChoudharyPlayerController::HandleToggleMathDebug()
{
	ShowInputDebugMessage(TEXT("Toggle Math Debug"));

	for (TActorIterator<AMathDebugVisualizer> It(GetWorld()); It; ++It)
	{
		It->ToggleDebugMode();
		break;
	}
}

void AAVP_RohanChoudharyPlayerController::HandleToggleObjectIDs()
{
	ShowInputDebugMessage(TEXT("Toggle Object IDs"));

	if (CachedManager)
	{
		CachedManager->ToggleObjectIDs();
	}
}

void AAVP_RohanChoudharyPlayerController::HandleRefreshDebug()
{
	ShowInputDebugMessage(TEXT("Refresh Debug"));

	for (TActorIterator<ATypePracticeDisplay> It(GetWorld()); It; ++It)
	{
		It->RefreshDisplay();
	}
}

void AAVP_RohanChoudharyPlayerController::HandleSaveTempNote()
{
	ShowInputDebugMessage(TEXT("Export Review Note"));

	if (!CachedManager) return;

	AArchSelectableObject* Selected = CachedManager->GetCurrentSelection();
	if (Selected)
	{
		FArchObjectInfo Info = Selected->GetObjectInfo();
		FString Msg;
		UBPL_ArchVizUtilities::ExportReviewNoteToCSV(
			Info.ObjectID.ToString(),
			Info.DisplayName.ToString(),
			Info.RoomName.ToString(),
			TEXT("Temporary Hardcoded Note Test"),
			Msg
		);
		ARCHVIZ_LOG(TEXT("Temp Export: %s"), *Msg);
	}
	else
	{
		ARCHVIZ_LOG(TEXT("Temp Export WARNING: No object selected to save temp note."));
	}
}

void AAVP_RohanChoudharyPlayerController::ShowInputDebugMessage(const FString& ActionName)
{
	// Suppressed on-screen debug messages as requested
}

void AAVP_RohanChoudharyPlayerController::ToggleControlsOverlay()
{
	ShowInputDebugMessage(TEXT("Toggle Controls Overlay (H Key)"));

	if (!ControlsOverlayWidget && ControlsOverlayWidgetClass)
	{
		ControlsOverlayWidget = CreateWidget<UUserWidget>(this, ControlsOverlayWidgetClass);
		if (ControlsOverlayWidget)
		{
			ControlsOverlayWidget->AddToViewport(15);
		}
	}
	else if (ControlsOverlayWidget)
	{
		if (ControlsOverlayWidget->GetVisibility() == ESlateVisibility::Visible ||
			ControlsOverlayWidget->GetVisibility() == ESlateVisibility::SelfHitTestInvisible)
		{
			ControlsOverlayWidget->SetVisibility(ESlateVisibility::Collapsed);
		}
		else
		{
			ControlsOverlayWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		}
	}
}

void AAVP_RohanChoudharyPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FHitResult Hit;
	bool bHit = false;

	if (bShowMouseCursor)
	{
		bHit = GetHitResultUnderCursor(ECC_Visibility, false, Hit);
	}
	else
	{
		FVector CameraLocation;
		FRotator CameraRotation;
		GetPlayerViewPoint(CameraLocation, CameraRotation);
		FVector End = CameraLocation + (CameraRotation.Vector() * 10000.f);
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(GetPawn());
		bHit = GetWorld()->LineTraceSingleByChannel(Hit, CameraLocation, End, ECC_Visibility, QueryParams);
	}

	AArchSelectableObject* HoveredObject = nullptr;
	if (bHit && Hit.GetActor())
	{
		HoveredObject = Cast<AArchSelectableObject>(Hit.GetActor());
	}

	if (CurrentHoveredObject != HoveredObject)
	{
		if (CurrentHoveredObject)
		{
			CurrentHoveredObject->SetHoveredState(false);
		}

		CurrentHoveredObject = HoveredObject;

		if (CurrentHoveredObject)
		{
			CurrentHoveredObject->SetHoveredState(true);
		}
	}
}

void AAVP_RohanChoudharyPlayerController::HandleBackPressed()
{
	if (CachedManager)
	{
		CachedManager->SelectObject(nullptr);
	}
}

void AAVP_RohanChoudharyPlayerController::SetNavigationMode(bool bCursorActive)
{
	bShowMouseCursor = bCursorActive;

	if (bCursorActive)
	{
		FInputModeGameAndUI InputMode;
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
		InputMode.SetHideCursorDuringCapture(false);
		SetInputMode(InputMode);
	}
	else
	{
		FInputModeGameOnly InputMode;
		SetInputMode(InputMode);
	}
}

void AAVP_RohanChoudharyPlayerController::HandleObjectSelectedStateChanged(const FArchObjectInfo& ObjectInfo)
{
	if (ObjectInfo.ObjectID.IsNone())
	{
		SetNavigationMode(false);
	}
	else
	{
		SetNavigationMode(true);
	}
}

void AAVP_RohanChoudharyPlayerController::HandleToggleFurniture()
{
	// Log the input event
	UE_LOG(LogTemp, Warning, TEXT("Toggle Furniture Data Layer input event received."));

	if (!FurnitureDataLayerAsset)
	{
		UE_LOG(LogTemp, Warning, TEXT("FurnitureDataLayerAsset is not assigned in the Player Controller!"));
		return;
	}

	UDataLayerSubsystem* DataLayerSubsystem = UWorld::GetSubsystem<UDataLayerSubsystem>(GetWorld());
	if (DataLayerSubsystem)
	{
		EDataLayerRuntimeState CurrentState = DataLayerSubsystem->GetDataLayerInstanceRuntimeState(FurnitureDataLayerAsset);
		EDataLayerRuntimeState NewState = (CurrentState == EDataLayerRuntimeState::Activated)
			? EDataLayerRuntimeState::Unloaded
			: EDataLayerRuntimeState::Activated;

		DataLayerSubsystem->SetDataLayerInstanceRuntimeState(FurnitureDataLayerAsset, NewState);

		FString StateStr = (NewState == EDataLayerRuntimeState::Activated) ? TEXT("Activated") : TEXT("Unloaded");
		UE_LOG(LogTemp, Warning, TEXT("Data Layer '%s' state changed to: %s"), *FurnitureDataLayerAsset->GetName(), *StateStr);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("DataLayerSubsystem not found!"));
	}
}

void AAVP_RohanChoudharyPlayerController::HandleToggleDoor()
{
	UE_LOG(LogTemp, Warning, TEXT("Toggle Door input event received (P Key)."));

	// Check if a door is currently selected and toggle it if so
	if (CachedManager)
	{
		AArchSelectableObject* Selected = CachedManager->GetCurrentSelection();
		if (Selected)
		{
			if (AArchAnimatedDoor* SelectedDoor = Cast<AArchAnimatedDoor>(Selected))
			{
				SelectedDoor->ToggleDoor();
				UE_LOG(LogTemp, Warning, TEXT("Toggled selected door: %s"), *SelectedDoor->GetName());
				return;
			}
		}
	}

	APawn* PlayerPawn = GetPawn();
	if (!PlayerPawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("HandleToggleDoor: Player Pawn not found!"));
		return;
	}

	FVector PlayerLoc = PlayerPawn->GetActorLocation();
	AArchAnimatedDoor* NearestDoor = nullptr;
	float NearestDistance = TNumericLimits<float>::Max();

	for (TActorIterator<AArchAnimatedDoor> It(GetWorld()); It; ++It)
	{
		AArchAnimatedDoor* Door = *It;
		if (Door)
		{
			float Dist = FVector::Distance(PlayerLoc, Door->GetActorLocation());
			if (Dist < NearestDistance)
			{
				NearestDistance = Dist;
				NearestDoor = Door;
			}
		}
	}

	if (NearestDoor)
	{
		NearestDoor->ToggleDoor();
		UE_LOG(LogTemp, Warning, TEXT("Toggled nearest door: %s"), *NearestDoor->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No ArchAnimatedDoor actors found in the level!"));
	}
}