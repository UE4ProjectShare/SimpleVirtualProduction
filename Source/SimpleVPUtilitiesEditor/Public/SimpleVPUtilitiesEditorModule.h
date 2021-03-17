// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "UObject/StrongObjectPtr.h"

class UOSCServer;

class FSimpleVPUtilitiesEditorModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

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
};
