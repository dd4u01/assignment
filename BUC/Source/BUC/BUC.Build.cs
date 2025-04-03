// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class BUC : ModuleRules
{
	public BUC(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", 
			// UI
			"UMG", "Slate", "SlateCore", 
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

        PrivateDependencyModuleNames.AddRange(new string[] { });

        PublicIncludePaths.AddRange(new string[] { "BUC" });
    }
}
