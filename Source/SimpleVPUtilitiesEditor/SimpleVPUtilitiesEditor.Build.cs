// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SimpleVPUtilitiesEditor : ModuleRules
{
	public SimpleVPUtilitiesEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
                "Blutility",
                "CoreUObject",
                "EditorSubsystem", 
                "SimpleVPUtilities",
                "VREditor",
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				// ... add private dependencies that you statically link with here ...	
				"EditorStyle",
				"GameplayTags",
				"LevelEditor",
				"Settings",
				"TimeManagement",
				"UMG",
				"UMGEditor",
				"UnrealEd",
				"SimpleVPBookmark",
				"WorkspaceMenuStructure",
				"CinematicCamera",
				"OSC",
				"PlacementMode"
			}
			);
	}
}
