// Copyright Epic Games, Inc. All Rights Reserved.

#include "SimpleVPUtilitiesEditorModule.h"

#include "ISettingsModule.h"
#include "ISettingsSection.h"
#include "LevelEditor.h"
#include "SimpleVPUtilitiesEditorSettings.h"
#include "OSCManager.h"
#include "OSCServer.h"
#include "SimpleVPSettings.h"

#define LOCTEXT_NAMESPACE "FSimpleVPUtilitiesEditorModule"

DEFINE_LOG_CATEGORY(LogSimpleVPUtilitiesEditor);

void FSimpleVPUtilitiesEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	RegisterSettings();
}

void FSimpleVPUtilitiesEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	UnregisterSettings();
}

void FSimpleVPUtilitiesEditorModule::RegisterSettings()
{
	ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");
	if (SettingsModule != nullptr)
	{
		ISettingsSectionPtr SettingsSection = SettingsModule->RegisterSettings("Project", "Plugins", "SimpleVP",
            LOCTEXT("SimpleVPSettingsName", "SimpleVP"),
            LOCTEXT("SimpleVPSettingsDescription", "Configure the Virtual Production settings."),
            GetMutableDefault<USimpleVPSettings>());

		ISettingsSectionPtr EditorSettingsSection = SettingsModule->RegisterSettings("Project", "Plugins", "SimpleVPEditor",
            LOCTEXT("SimpleVPEditorSettingsName", "SimpleVP Editor"),
            LOCTEXT("SimpleVPEditorSettingsDescription", "Configure the Virtual Production Editor settings."),
            GetMutableDefault<USimpleVPUtilitiesEditorSettings>());

		EditorSettingsSection->OnModified().BindRaw(this, &FSimpleVPUtilitiesEditorModule::OnSettingsModified);
	}

	/*FLevelEditorModule* LevelEditorModule = FModuleManager::GetModulePtr<FLevelEditorModule>("LevelEditor");
	if (LevelEditorModule != nullptr)
	{
		FLevelEditorModule::FStatusBarItem Item;
		Item.Label = LOCTEXT("VPRolesLabel", "VP Roles: ");
		Item.Value = MakeAttributeLambda([]() { return FText::FromString(GetMutableDefault<UVPSettings>()->GetRoles().ToStringSimple()); });
		Item.Visibility = MakeAttributeLambda([]() { return GetMutableDefault<UVPSettings>()->bShowRoleInEditor ? EVisibility::SelfHitTestInvisible : EVisibility::Collapsed; });
		LevelEditorModule->AddStatusBarItem(VPRoleNotificationBarIdentifier, Item);
	}*/
}

void FSimpleVPUtilitiesEditorModule::UnregisterSettings()
{
	/*ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");
	if (SettingsModule != nullptr)
	{
		SettingsModule->UnregisterSettings("Project", "Plugins", "VirtualProduction");
		SettingsModule->UnregisterSettings("Project", "Plugins", "VirtualProductionEditor");
	}

	FLevelEditorModule* LevelEditorModule = FModuleManager::GetModulePtr<FLevelEditorModule>("LevelEditor");
	if (LevelEditorModule != nullptr)
	{
		LevelEditorModule->RemoveStatusBarItem(VPRoleNotificationBarIdentifier);
	}*/
}

void FSimpleVPUtilitiesEditorModule::InitializeOSCServer()
{
}

bool FSimpleVPUtilitiesEditorModule::OnSettingsModified()
{
	const USimpleVPUtilitiesEditorSettings* Settings = GetDefault<USimpleVPUtilitiesEditorSettings>();
	if (Settings->bStartOSCServerAtLaunch)
	{
		InitializeOSCServer();
	}
	else if(OSCServer)
	{
		OSCServer->Stop();
	}


	//todo 什么意思
	IConsoleVariable* GizmoCVar = IConsoleManager::Get().FindConsoleVariable(TEXT("VI.ShowTransformGizmo"));
	GizmoCVar->Set(Settings->bUseTransformGizmo);

	IConsoleVariable* InertiaCVar = IConsoleManager::Get().FindConsoleVariable(TEXT("VI.HighSpeedInertiaDamping"));
	InertiaCVar->Set(Settings->bUseGripInertiaDamping ? Settings->InertiaDamping : 0);
	return true;
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FSimpleVPUtilitiesEditorModule, SimpleVPUtilitiesEditor)