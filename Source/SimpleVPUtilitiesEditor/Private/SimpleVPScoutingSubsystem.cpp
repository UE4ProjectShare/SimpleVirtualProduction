// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleVPScoutingSubsystem.h"

#include "IVREditorModule.h"
#include "SimpleVPUtilitiesEditorModule.h"

#include "LevelEditorActions.h"
#include "SimpleVPUtilitiesEditorSettings.h"
#include "VREditorMode.h"
#include "UI/VREditorUISystem.h"

const FName USimpleVPScoutingSubsystem::VProdPanelID = FName(TEXT("VirtualProductionPanel"));
const FName USimpleVPScoutingSubsystem::VProdPanelLeftID = FName(TEXT("VirtualProductionPanelLeft"));
const FName USimpleVPScoutingSubsystem::VProdPanelRightID = FName(TEXT("VirtualProductionPanelRight"));
const FName USimpleVPScoutingSubsystem::VProdPanelContextID = FName(TEXT("VirtualProductionPanelContext"));
const FName USimpleVPScoutingSubsystem::VProdPanelTimelineID = FName(TEXT("VirtualProductionPanelTimeline"));
const FName USimpleVPScoutingSubsystem::VProdPanelMeasureID = FName(TEXT("VirtualProductionPanelMeasure"));
const FName USimpleVPScoutingSubsystem::VProdPanelGafferID = FName(TEXT("VirtualProductionPanelGaffer"));

USimpleVPScoutingSubsystem::USimpleVPScoutingSubsystem()
:	UEditorSubsystem(),
	GripNavSpeedCoeff(4.0f)
{
}

void USimpleVPScoutingSubsystem::ToggleVRScoutingUI(FVREditorFloatingUICreationContext& CreationContext)
{
	// @todo: Add lookup like like bool UVREditorUISystem::EditorUIPanelExists(const VREditorPanelID& InPanelID) const
	// Return if users try to create a panel that already exists
		
	if (CreationContext.WidgetClass == nullptr || CreationContext.PanelID == TEXT(""))
	{
		UE_LOG(LogSimpleVPUtilitiesEditor, Warning, TEXT("USimpleVPScoutingSubsystem::ToggleVRScoutingUI - WidgetClass or PanelID can't be null."));
		return; // @todo: Remove early rejection code, hook up UVPSettings::VirtualScoutingUI instead
	}
	
	// Account for actors trying to call this function from their destructor when VR mode ends (UI system is one of the earliest systems getting shut down)	
	UVREditorMode const* const VRMode = IVREditorModule::Get().GetVRMode();
	if (VRMode && VRMode->UISystemIsActive())
	{
		bool bPanelVisible = VRMode->GetUISystem().IsShowingEditorUIPanel(CreationContext.PanelID);

		// Close panel if currently visible
		if (bPanelVisible)
		{
			// Close the existing panel by passing null as the widget. We don't care about any of the other parameters in this case
			CreationContext.WidgetClass = nullptr;
			CreationContext.PanelSize = FVector2D(1, 1); // Guard against 0,0 user input. The actual size is not important when closing a panel, but a check() would trigger
			IVREditorModule::Get().UpdateExternalUMGUI(CreationContext);
		}
		else // Otherwise open a new one - with the user-defined VProd UI being the default
		{
			// @todo: Currently won't ever be true
			if (CreationContext.WidgetClass == nullptr)
			{
				const TSoftClassPtr<UEditorUtilityWidget> WidgetClass = GetDefault<USimpleVPUtilitiesEditorSettings>()->VirtualScoutingUI;
				WidgetClass.LoadSynchronous();
				if (WidgetClass.IsValid())
				{
					CreationContext.WidgetClass = WidgetClass.Get();
				}
			}

			if (CreationContext.WidgetClass != nullptr)
			{
				IVREditorModule::Get().UpdateExternalUMGUI(CreationContext);
			}
			else
			{
				UE_LOG(LogSimpleVPUtilitiesEditor, Warning, TEXT("USimpleVPScoutingSubsystem::ToggleVRScoutingUI - Failed to open widget-based VR window."));
			}
		}
	}
}

bool USimpleVPScoutingSubsystem::IsVRScoutingUIOpen(const FName& PanelID)
{
	return IVREditorModule::Get().GetVRMode()->GetUISystem().IsShowingEditorUIPanel(PanelID);
}

AVREditorFloatingUI* USimpleVPScoutingSubsystem::GetPanelActor(const FName& PanelID) const
{
	return IVREditorModule::Get().GetVRMode()->GetUISystem().GetPanel(PanelID);
}

UUserWidget* USimpleVPScoutingSubsystem::GetPanelWidget(const FName& PanelID) const
{
	AVREditorFloatingUI* Panel = GetPanelActor(PanelID);
	if (Panel == nullptr)
	{
		return nullptr;
	}
	else
	{
		return Panel->GetUserWidget();
	}
}

TArray<UVREditorInteractor*> USimpleVPScoutingSubsystem::GetActiveEditorVRControllers()
{
	IVREditorModule& VREditorModule = IVREditorModule::Get();
	UVREditorMode* VRMode = VREditorModule.GetVRMode();
	
	const TArray<UVREditorInteractor*> Interactors = VRMode->GetVRInteractors();
	ensureMsgf(Interactors.Num() == 2, TEXT("Expected 2 VR controllers from VREditorMode, got %d"), Interactors.Num());
	return Interactors;	
}

bool USimpleVPScoutingSubsystem::IsUsingMetricSystem()
{
	return GetDefault<USimpleVPUtilitiesEditorSettings>()->bUseMetric;
}

void USimpleVPScoutingSubsystem::SetIsUsingMetricSystem(const bool bInUseMetricSystem)
{
	USimpleVPUtilitiesEditorSettings* VPUtilitiesEditorSettings = GetMutableDefault<USimpleVPUtilitiesEditorSettings>();
	VPUtilitiesEditorSettings->bUseMetric = bInUseMetricSystem;
	VPUtilitiesEditorSettings->SaveConfig();
}

bool USimpleVPScoutingSubsystem::IsUsingTransformGizmo()
{
	return GetDefault<USimpleVPUtilitiesEditorSettings>()->bUseTransformGizmo;
}

void USimpleVPScoutingSubsystem::SetIsUsingTransformGizmo(const bool bInIsUsingTransformGizmo)
{
	USimpleVPUtilitiesEditorSettings* VPUtilitiesEditorSettings = GetMutableDefault<USimpleVPUtilitiesEditorSettings>();
	if (bInIsUsingTransformGizmo != VPUtilitiesEditorSettings->bUseTransformGizmo)
	{
		VPUtilitiesEditorSettings->bUseTransformGizmo = bInIsUsingTransformGizmo;
		SetShowTransformGizmoCVar(bInIsUsingTransformGizmo);
		VPUtilitiesEditorSettings->SaveConfig();
	}
}

void USimpleVPScoutingSubsystem::SetShowTransformGizmoCVar(const bool bInShowTransformGizmoCVar)
{
	IConsoleVariable* CVar = IConsoleManager::Get().FindConsoleVariable(TEXT("VI.ShowTransformGizmo"));
	CVar->Set(bInShowTransformGizmoCVar);
}

float USimpleVPScoutingSubsystem::GetFlightSpeed()
{
	return GetDefault<USimpleVPUtilitiesEditorSettings>()->FlightSpeed;
}

void USimpleVPScoutingSubsystem::SetFlightSpeed(const float InFlightSpeed)
{
	USimpleVPUtilitiesEditorSettings* VPUtilitiesEditorSettings = GetMutableDefault<USimpleVPUtilitiesEditorSettings>();
	VPUtilitiesEditorSettings->FlightSpeed = InFlightSpeed;
	VPUtilitiesEditorSettings->SaveConfig();
}

float USimpleVPScoutingSubsystem::GetGripNavSpeed()
{
	return GetDefault<USimpleVPUtilitiesEditorSettings>()->GripNavSpeed;
}

void USimpleVPScoutingSubsystem::SetGripNavSpeed(const float InGripNavSpeed)
{
	USimpleVPUtilitiesEditorSettings* VPUtilitiesEditorSettings = GetMutableDefault<USimpleVPUtilitiesEditorSettings>();
	VPUtilitiesEditorSettings->GripNavSpeed = InGripNavSpeed;
	VPUtilitiesEditorSettings->SaveConfig();
}

bool USimpleVPScoutingSubsystem::IsUsingInertiaDamping()
{
	return GetDefault<USimpleVPUtilitiesEditorSettings>()->bUseGripInertiaDamping;
}

void USimpleVPScoutingSubsystem::SetIsUsingInertiaDamping(const bool bInIsUsingInertiaDamping)
{
	//Save this value in editor settings and set the console variable which is used for inertia damping
	USimpleVPUtilitiesEditorSettings* VPUtilitiesEditorSettings = GetMutableDefault<USimpleVPUtilitiesEditorSettings>();
	VPUtilitiesEditorSettings->bUseGripInertiaDamping = bInIsUsingInertiaDamping;
	
	if (bInIsUsingInertiaDamping)
	{
		SetInertiaDampingCVar(VPUtilitiesEditorSettings->InertiaDamping);
	}
	else
	{
		SetInertiaDampingCVar(0);
	}
	VPUtilitiesEditorSettings->SaveConfig();
}

void USimpleVPScoutingSubsystem::SetInertiaDampingCVar(const float InInertiaDamping)
{
	IConsoleVariable* CVar = IConsoleManager::Get().FindConsoleVariable(TEXT("VI.HighSpeedInertiaDamping"));
	CVar->Set(InInertiaDamping);
}

bool USimpleVPScoutingSubsystem::IsHelperSystemEnabled()
{
	return GetDefault<USimpleVPUtilitiesEditorSettings>()->bIsHelperSystemEnabled;
}

void USimpleVPScoutingSubsystem::SetIsHelperSystemEnabled(const bool bInIsHelperSystemEnabled)
{
	USimpleVPUtilitiesEditorSettings* VPUtilitiesEditorSettings = GetMutableDefault<USimpleVPUtilitiesEditorSettings>();
	VPUtilitiesEditorSettings->bIsHelperSystemEnabled = bInIsHelperSystemEnabled;
	VPUtilitiesEditorSettings->SaveConfig();
}

void USimpleVPScoutingSubsystem::ExitVRMode()
{
	IVREditorModule& VREditorModule = IVREditorModule::Get();
	if (VREditorModule.IsVREditorEnabled())
	{
		VREditorModule.EnableVREditor(false);
	}
}

bool USimpleVPScoutingSubsystem::IsLocationGridSnappingEnabled()
{
	return FLevelEditorActionCallbacks::LocationGridSnap_IsChecked();
}

void USimpleVPScoutingSubsystem::ToggleLocationGridSnapping()
{
	FLevelEditorActionCallbacks::LocationGridSnap_Clicked();
}

bool USimpleVPScoutingSubsystem::IsRotationGridSnappingEnabled()
{
	return FLevelEditorActionCallbacks::RotationGridSnap_IsChecked();
}

void USimpleVPScoutingSubsystem::ToggleRotationGridSnapping()
{
	FLevelEditorActionCallbacks::RotationGridSnap_Clicked();
}
