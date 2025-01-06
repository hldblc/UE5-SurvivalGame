// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;


public class SurvivalGame : ModuleRules
{
    public SurvivalGame(ReadOnlyTargetRules Target) : base(Target)
    {
        // Use explicit or shared PCHs to improve compilation times
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        bLegacyPublicIncludePaths = false;

        // Add Common UI Path
        PublicIncludePaths.AddRange(
            new [] {
                "SurvivalGame/Components",
                "SurvivalGame/Data",
                "SurvivalGame/Characters",
                "SurvivalGame/Enums"
                // Add other public include paths here if necessary
            }
        );

        // Removed redundant PrivateIncludePaths since all includes are now in PublicIncludePaths

        // Public dependencies required for gameplay functionality
        PublicDependencyModuleNames.AddRange(new[]
        {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "EnhancedInput",
            "GameplayAbilities",
            "GameplayTags",
            "GameplayTasks",
            "AIModule",
            "NavigationSystem",
            "CommonUI",
            "UMG",
            "Slate",
            "SlateCore",
            "CommonInput"
        });

        // Private dependencies for low-level or engine-specific functionalities
        PrivateDependencyModuleNames.AddRange(new[]
        {
            "NetCore",
            "RenderCore",
            "DeveloperSettings",
            "PhysicsCore",
            "Chaos",
            "ChaosSolverEngine",
            "RHI",
            "AssetRegistry",
            "ApplicationCore"
        });

        // Developer-only dependencies for editor and development builds
        if (Target.bBuildEditor)
        {
            PrivateDependencyModuleNames.AddRange(new[]
            {
                "UnrealEd",
                "EditorFramework",
                "EditorStyle",
                "EditorSubsystem"
            });
        }

        // Add gameplay debugger for non-shipping builds
        if (Target.Configuration != UnrealTargetConfiguration.Shipping)
        {
            PublicDefinitions.Add("WITH_GAMEPLAY_DEBUGGER=1");
            PublicDependencyModuleNames.Add("GameplayDebugger");
        }
        else
        {
            PublicDefinitions.Add("WITH_GAMEPLAY_DEBUGGER=0");
        }

        // Optimization settings for faster iteration and performance
        bUseUnity = false; // Disable Unity builds for smaller builds during iteration
        MinFilesUsingPrecompiledHeaderOverride = 1; // Use PCH for all files
        bUseRTTI = false; // Disable RTTI for performance
        bEnableExceptions = false; // Disable C++ exceptions

        // Dynamically loaded modules for online functionalities
        DynamicallyLoadedModuleNames.AddRange(new[]
        {
            "OnlineSubsystem",
            "OnlineSubsystemUtils"
        });

        // Ensure additional dependencies for OnlineSubsystem are included if necessary
        // For example, if you're using specific online subsystems like Steam, add them here
        // PrivateDependencyModuleNames.Add("OnlineSubsystemSteam");
    }
}
