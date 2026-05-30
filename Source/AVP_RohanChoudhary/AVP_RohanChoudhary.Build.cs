// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AVP_RohanChoudhary : ModuleRules
{
	public AVP_RohanChoudhary(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"AVP_RohanChoudhary",
			"AVP_RohanChoudhary/Variant_Platforming",
			"AVP_RohanChoudhary/Variant_Platforming/Animation",
			"AVP_RohanChoudhary/Variant_Combat",
			"AVP_RohanChoudhary/Variant_Combat/AI",
			"AVP_RohanChoudhary/Variant_Combat/Animation",
			"AVP_RohanChoudhary/Variant_Combat/Gameplay",
			"AVP_RohanChoudhary/Variant_Combat/Interfaces",
			"AVP_RohanChoudhary/Variant_Combat/UI",
			"AVP_RohanChoudhary/Variant_SideScrolling",
			"AVP_RohanChoudhary/Variant_SideScrolling/AI",
			"AVP_RohanChoudhary/Variant_SideScrolling/Gameplay",
			"AVP_RohanChoudhary/Variant_SideScrolling/Interfaces",
			"AVP_RohanChoudhary/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
