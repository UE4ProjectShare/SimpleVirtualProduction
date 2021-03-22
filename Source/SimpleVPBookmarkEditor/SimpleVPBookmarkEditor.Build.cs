// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SimpleVPBookmarkEditor : ModuleRules
{
	public SimpleVPBookmarkEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"SimpleVPBookmark",
				"Core",
				"CoreUObject",
				"Engine",
				"SlateCore"

			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"EditorStyle",
				"HeadMountedDisplay",
				"InputCore",
				"LevelEditor",
				"Slate",
				"ViewportInteraction",
				"VREditor",
				"UnrealEd"
			}
			);

	}
}
