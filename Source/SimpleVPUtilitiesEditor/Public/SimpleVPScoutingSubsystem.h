// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorSubsystem.h"
#include "VREditorInteractor.h"
#include "UI/VREditorFloatingUI.h"

#include "SimpleVPScoutingSubsystem.generated.h"


UENUM(BlueprintType)
enum class EVPPanelIDs : uint8
{
	MainUI,
    LeftUI,
    RightUI,
    ContextUI,
    TimelineUI,
    MeasureUI,
    GafferUI
};

/*
* Base class of the helper class defined in BP
*/
UCLASS(Abstract, Blueprintable, MinimalAPI, meta = (ShowWorldContextPin))
class USimpleVPScoutingSubsystemHelpersBase : public UObject
{
	GENERATED_BODY()
};

/**
 * 
 */
UCLASS()
class USimpleVPScoutingSubsystem : public UEditorSubsystem
{
	GENERATED_BODY()
public:
	USimpleVPScoutingSubsystem();

	/** Subsystems can't have any Blueprint implementations, so we attach this class for any BP logic that we to provide. */
	UPROPERTY(Transient, BlueprintReadOnly, Category = "Virtual Production")
	USimpleVPScoutingSubsystemHelpersBase* VPSubsystemHelpers;

	/** bool to keep track of whether the settings menu panel in the main menu is open*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Menu")
	bool IsSettingsMenuOpen;
	
	/** This is a multiplier for grip nav speed so we can keep the grip nav value in the range 0-1 and increase this variable if we need a bigger range */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Virtual Production")
	float GripNavSpeedCoeff;

	// @todo: Guard against user-created name collisions
	/** Open a widget UI in front of the user. Opens default VProd UI (defined via the 'Virtual Scouting User Interface' setting) if null. */
	UFUNCTION(BlueprintCallable, Category = "Virtual Production")
    void ToggleVRScoutingUI(UPARAM(ref) FVREditorFloatingUICreationContext& CreationContext);

	/** Check whether a widget UI is open*/
	UFUNCTION(BlueprintPure, Category = "Virtual Production")
    bool IsVRScoutingUIOpen(const FName& PanelID);
	
	/** Get UI panel Actor from the passed ID */
	UFUNCTION(BlueprintPure, Category = "Virtual Production")
    AVREditorFloatingUI* GetPanelActor(const FName& PanelID) const;
	
	/** Get UI panel widget from the passed ID */
	UFUNCTION(BlueprintPure, Category = "Virtual Production")
    UUserWidget* GetPanelWidget(const FName& PanelID) const;

	UFUNCTION(BlueprintCallable, Category = "Virtual Production")
	static TArray<UVREditorInteractor*> GetActiveEditorVRControllers();
	
	UFUNCTION(BlueprintPure, Category = "Virtual Production")
	static const FName GetVProdPanelID(const EVPPanelIDs Panel)
	{
		switch (Panel)
		{
		case EVPPanelIDs::MainUI:
			return VProdPanelID;
		case EVPPanelIDs::RightUI:
			return VProdPanelRightID;
		case EVPPanelIDs::LeftUI:
			return VProdPanelLeftID;
		case EVPPanelIDs::ContextUI:
			return VProdPanelContextID;
		case EVPPanelIDs::TimelineUI:
			return VProdPanelTimelineID;
		case EVPPanelIDs::MeasureUI:
			return VProdPanelMeasureID;
		case EVPPanelIDs::GafferUI:
			return VProdPanelGafferID;
		}

		return VProdPanelID;
	};

	/** Whether the VR user wants to use the metric system instead of imperial */
	UFUNCTION(BlueprintPure, Category = "Virtual Production")
    static bool IsUsingMetricSystem();

	/** Set whether the VR user wants to use the metric system instead of imperial */
	UFUNCTION(BlueprintCallable, Category = "Virtual Production")
    static void SetIsUsingMetricSystem(const bool bInUseMetricSystem);
	
	/** Whether the VR user wants to have the transform gizmo enabled */
	UFUNCTION(BlueprintPure, Category = "Virtual Production")
    static bool IsUsingTransformGizmo();

	/** Set whether the VR user wants to have the transform gizmo enabled */
	UFUNCTION(BlueprintCallable, Category = "Virtual Production")
    static void SetIsUsingTransformGizmo(const bool bInIsUsingTransformGizmo);

	/** Set value of cvar "VI.ShowTransformGizmo" */
	UFUNCTION(BlueprintCallable, Category = "Virtual Production")
    static void SetShowTransformGizmoCVar(const bool bInShowTransformGizmoCVar);

	/** Get flight speed for scouting in VR */
	UFUNCTION(BlueprintPure, Category = "Virtual Production")
    static float GetFlightSpeed();

	/** Set flight speed for scouting in VR */
	UFUNCTION(BlueprintCallable, Category = "Virtual Production")
    static void SetFlightSpeed(const float InFlightSpeed);
	
	/** Get grip nav speed for scouting in VR */
	UFUNCTION(BlueprintPure, Category = "Virtual Production")
    static float GetGripNavSpeed();

	/** Set grip nav speed for scouting in VR */
	UFUNCTION(BlueprintCallable, Category = "Virtual Production")
    static void SetGripNavSpeed(const float InGripNavSpeed);

	/** Whether grip nav inertia is enabled when scouting in VR */
	UFUNCTION(BlueprintPure, Category = "Virtual Production")
    static bool IsUsingInertiaDamping();

	/** Set whether grip nav inertia is enabled when scouting in VR */
	UFUNCTION(BlueprintCallable, Category = "Virtual Production")
    static void SetIsUsingInertiaDamping(const bool bInIsUsingInertiaDamping);

	/** Set value of cvar "VI.HighSpeedInertiaDamping" */
	UFUNCTION(BlueprintCallable, Category = "Virtual Production")
    static void SetInertiaDampingCVar(const float InInertiaDamping);

	/** Whether the helper system on the controllers is enabled */
	UFUNCTION(BlueprintPure, Category = "Virtual Production")
    static bool IsHelperSystemEnabled();

	/** Set whether the helper system on the controllers is enabled   */
	UFUNCTION(BlueprintCallable, Category = "Virtual Production")
    static void SetIsHelperSystemEnabled(const bool bInIsHelperSystemEnabled);
	
	/** Exit VR Mode  */
	UFUNCTION(BlueprintCallable, Category = "Virtual Production")
    static void ExitVRMode();
	
	/** Whether location grid snapping is enabled */
	UFUNCTION(BlueprintCallable, Category = "Virtual Production")
    static bool IsLocationGridSnappingEnabled();

	/** Toggle location grid snapping */
	UFUNCTION(BlueprintCallable, Category = "Virtual Production")
    static void ToggleLocationGridSnapping();

	/** Whether rotation grid snapping is enabled */
	UFUNCTION(BlueprintCallable, Category = "Virtual Production")
    static bool IsRotationGridSnappingEnabled();

	/** Toggle rotation grid snapping */
	UFUNCTION(BlueprintCallable, Category = "Virtual Production")
    static void ToggleRotationGridSnapping();

private:
	// Static IDs when submitting open/close requests for the VProd main menu panels. VREditorUISystem uses FNames to manage its panels, so these should be used for consistency.	
	static const FName VProdPanelID;
	static const FName VProdPanelLeftID;
	static const FName VProdPanelRightID;
	static const FName VProdPanelContextID;
	static const FName VProdPanelTimelineID;
	static const FName VProdPanelMeasureID;
	static const FName VProdPanelGafferID;
	
};
