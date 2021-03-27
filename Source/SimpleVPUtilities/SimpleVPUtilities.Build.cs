// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SimpleVPUtilities : ModuleRules
{
	public SimpleVPUtilities(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
				"CinematicCamera",
                "Composure",
                "CoreUObject",
                "Engine",
                "GameplayTags",
                "TimeManagement",
                "UMG",
                "SimpleVPBookmark"
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"ApplicationCore",
				"RenderCore",
				"RHI",
				"Slate",
				"SlateCore",
				// ... add private dependencies that you statically link with here ...	
			}
			);
		if (Target.Type == TargetType.Editor)
		{
			PrivateDependencyModuleNames.AddRange(
				new string[]
				{
					"Blutility",
					"LevelEditor",
					"UnrealEd",
					"ViewportInteraction",
					"VREditor",
					"SimpleVPBookmarkEditor"
				}
			);
		}
	}
}
