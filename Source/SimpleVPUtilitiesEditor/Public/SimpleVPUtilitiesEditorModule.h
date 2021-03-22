// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "ISimpleUtilitiesEditorModule.h"
#include "Modules/ModuleManager.h"
#include "UObject/StrongObjectPtr.h"

DECLARE_LOG_CATEGORY_EXTERN(LogSimpleVPUtilitiesEditor, Log, Log);

class UOSCServer;

class FSimpleVPUtilitiesEditorModule : public ISimpleVPUtilitiesEditorModule
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	/**
	* Get an OSC server that can be started at the module's startup.
	*/
	virtual UOSCServer* GetOSCServer() const override;

	/**
	* Returns the Placement Mode Info for the Virtual Production category.
	* The category will be registered if it has not already been.
	*/
	virtual const FPlacementCategoryInfo* GetVirtualProductionPlacementCategoryInfo() const override;

private:
	/** Register VPUtilities settings. */
	void RegisterSettings();

	/** Unregister VPUtilities settings */
	void UnregisterSettings();

	/** Start an OSC server and bind a an OSC listener to it. */
	void InitializeOSCServer();

	/** Handler for when VP utilities settings are changed. */
	bool OnSettingsModified();

private:
	/**
	* Specific implementation of FGCObject that prevents a single UObject-based pointer from being GC'd while this guard is in scope.
	* @note This is the "full-fat" version of FGCObjectScopeGuard which uses a heap-allocated FGCObject so *can* safely be used with containers that treat types as trivially relocatable.
	*/
	
	/** The default OSC server. */
	TStrongObjectPtr<UOSCServer> OSCServer;

	/** Virtual production role identifier for the notification bar. */
	static const FName VPRoleNotificationBarIdentifier;

	/** UI Handler for virtual scouting. */
	//TStrongObjectPtr<UVPCustomUIHandler> CustomUIHandler;

	/** Unique Handle for the Virtual Production Placement Mode Category */
	static const FName PlacementModeCategoryHandle;
};
