using UnrealBuildTool;

public class AssetGenerator : ModuleRules
{
    public AssetGenerator(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        CppStandard = CppStandardVersion.Cpp20;
        bLegacyPublicIncludePaths = false;
        ShadowVariableWarningLevel = WarningLevel.Off;
        
        PublicDependencyModuleNames.AddRange(new[] {
            "Core", 
            "CoreUObject",
            "Engine",
            "InputCore",
            "BlueprintGraph",
            "KismetCompiler",
            "AssetRegistry",
            "SlateCore", "Slate", "UMG",
            "Projects",
            "Landscape",
            "Json",
			"UnrealEd",
            "UMGEditor",
			"BlueprintGraph",
            "MovieSceneTracks",
            "AssetDumper",
            "EditorStyle"
        });
        
		PrivateDependencyModuleNames.AddRange(new[] {
            "DesktopPlatform",
            "MaterialEditor",
            "RHI", 
            "AnimGraph",
            "Kismet",
            "WorkspaceMenuStructure",
            "PhysicsCore",
            "MediaAssets",
            "AudioEditor",
            "GraphEditor",
            "WwiseFileHandler", "AkAudio"
        });

	    PrivateDependencyModuleNames.Add("DeveloperSettings");
    }
}
