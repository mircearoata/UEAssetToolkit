#include "Toolkit/AssetTypeGenerator/DataAssetGenerator.h"

#include "AssetRegistry/AssetRegistryModule.h"
#include "AssetRegistry/IAssetRegistry.h"

UClass* UDataAssetGenerator::GetAssetObjectClass() const {
	return FindObjectChecked<UClass>(NULL, *GetAssetClassPath().ToString());
}

FTopLevelAssetPath UDataAssetGenerator::GetAssetClass() {
	return FTopLevelAssetPath(UDataAsset::StaticClass());
}

void UDataAssetGenerator::GetAdditionallyHandledAssetClasses(TArray<FTopLevelAssetPath>& OutExtraAssetClasses) {
	// Handle any UDataAsset-derived classes
	TArray<UClass*> DerivedClasses;
	GetDerivedClasses(UDataAsset::StaticClass(), DerivedClasses, true);
	for (UClass* DerivedClass : DerivedClasses) {
		OutExtraAssetClasses.Add(FTopLevelAssetPath(DerivedClass));
	}

	IAssetRegistry& AssetRegistry = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry").Get();
	FARFilter Filter;
	Filter.ClassPaths.Add(FTopLevelAssetPath(UBlueprint::StaticClass()));
	for (const UClass* DerivedClass : DerivedClasses) {
		Filter.TagsAndValues.Add(FBlueprintTags::NativeParentClassPath, FString::Printf(TEXT("%s'%s'"), *DerivedClass->GetClass()->GetPathName(), *DerivedClass->GetPathName()));
	}
	Filter.bRecursiveClasses = true;
	TArray<FAssetData> BlueprintDataAssets;
	AssetRegistry.GetAssets(Filter, BlueprintDataAssets);
	for (const FAssetData& BlueprintDataAsset : BlueprintDataAssets) {
		FString GeneratedClassPath;
		BlueprintDataAsset.GetTagValue(FBlueprintTags::GeneratedClassPath, GeneratedClassPath);
		OutExtraAssetClasses.Add(FTopLevelAssetPath(GeneratedClassPath));
	}
}
