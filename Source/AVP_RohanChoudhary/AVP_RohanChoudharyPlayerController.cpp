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

#include "EngineUtils.h"

void AAVP_RohanChoudharyPlayerController::BeginPlay()
{
	Super::BeginPlay();

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

	bShowMouseCursor = true;
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

	GetHitResultUnderCursor(
		ECC_Visibility,
		false,
		Hit);

	AArchSelectableObject* Object =
		Cast<AArchSelectableObject>(
			Hit.GetActor());

	if (Object)
	{
		UE_LOG(
			LogTemp,
			Warning,
			TEXT("Hit Object: %s"),
			*Object->GetName());
	}
	else
	{
		UE_LOG(
			LogTemp,
			Warning,
			TEXT("Hit Actor but NOT ArchSelectableObject"));
	}

	if (!Object)
	{
		return;
	}

	if (CachedManager)
	{
		CachedManager->SelectObject(Object);
	}
}

void AAVP_RohanChoudharyPlayerController::HandleToggleMathDebug()
{
	for (TActorIterator<AMathDebugVisualizer> It(GetWorld()); It; ++It)
	{
		It->ToggleDebugMode();
		break;
	}
}

void AAVP_RohanChoudharyPlayerController::HandleToggleObjectIDs()
{
	if (CachedManager)
	{
		CachedManager->ToggleObjectIDs();
	}
}