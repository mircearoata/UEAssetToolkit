// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.IO;
using EpicGames.Core;

public class AssetDumper : ModuleRules
{
    public AssetDumper(ReadOnlyTargetRules Target) : base(Target)
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
	        "AnimGraphRuntime",
	        "AssetRegistry",
	        "SlateCore", "Slate", "UMG",
	        "Landscape",
            "Json",
            "MovieScene",
            "Projects",
			"RenderCore",
			"MovieScene",
			"MovieSceneTracks"
        });

        PrivateDependencyModuleNames.AddRange(new[] {
	        "PhysicsCore",
	        "RHI", 
	        "MediaAssets"
        });
        
        if (Target.bBuildEditor) {
            PublicDependencyModuleNames.Add("UnrealEd");
            PrivateDependencyModuleNames.Add("MainFrame");
        }
        
        var thirdPartyFolder = Path.Combine(ModuleDirectory, "../../ThirdParty");
        PublicIncludePaths.Add(Path.Combine(thirdPartyFolder, "include"));
        
        var platformName = Target.Platform.ToString();
        var libraryFolder = Path.Combine(thirdPartyFolder, platformName);

        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
	        PublicAdditionalLibraries.Add(Path.Combine(libraryFolder, "libfbxsdk-md.lib"));
	        PublicAdditionalLibraries.Add(Path.Combine(libraryFolder, "libxml2-md.lib"));
	        PublicAdditionalLibraries.Add(Path.Combine(libraryFolder, "zlib-md.lib"));
	        PublicAdditionalLibraries.Add(Path.Combine(libraryFolder, "detex.lib"));
        }
        else if (Target.IsInPlatformGroup(UnrealPlatformGroup.Unix))
        {
	        PublicAdditionalLibraries.Add(Path.Combine(libraryFolder, "libxml2.a"));
	        PublicAdditionalLibraries.Add(Path.Combine(libraryFolder, "libz.a"));
	        PublicAdditionalLibraries.Add(Path.Combine(libraryFolder, "libdetex.a"));

	        // On Windows we use a static library. I have no idea how, as the fbx sdk only provides a shared library build
	        // For linux let's just do what UE does and link the shared library
	        // This does mean that two libfbxsdk.so will be loaded, but we're not going to dump assets in a Linux (Editor) build anyway
	        PublicDefinitions.Add("FBXSDK_SHARED");

	        PublicRuntimeLibraryPaths.Add(libraryFolder);
	        PublicAdditionalLibraries.Add(Path.Combine(libraryFolder, "libfbxsdk.so"));
	        RuntimeDependencies.Add(Path.Combine(libraryFolder, "libfbxsdk.so"));

	        /* There is a bug in fbxarch.h where is doesn't do the check
	         * for clang under linux */
	        PublicDefinitions.Add("FBXSDK_COMPILER_CLANG");

	        // libfbxsdk has been built against libstdc++ and as such needs this library
	        PublicSystemLibraries.Add("stdc++");
        }
        
        var pluginsDirectory = DirectoryReference.Combine(Target.ProjectFile.Directory, "Plugins");
        var smlPluginDirectory = DirectoryReference.Combine(pluginsDirectory, "SML");
        
        var modsDirectory = DirectoryReference.Combine(Target.ProjectFile.Directory, "Mods");
        var smlModDirectory = DirectoryReference.Combine(modsDirectory, "SML");
        
        if (Directory.Exists(smlPluginDirectory.FullName) || Directory.Exists(smlModDirectory.FullName)) {
	        PrivateDependencyModuleNames.Add("SML");
	        PublicDefinitions.Add("METHOD_PATCHING_SUPPORTED=1");
        }
    }
}
