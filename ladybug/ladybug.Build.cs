// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ladybug : ModuleRules
{
	public ladybug(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "UMG", "Slate", "SlateCore", "GameplayTasks", "MoviePlayer", "GameplayTags", "Niagara" });
	}
}
