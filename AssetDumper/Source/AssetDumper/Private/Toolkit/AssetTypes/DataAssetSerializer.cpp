#include "Toolkit/AssetTypes/DataAssetSerializer.h"

#include "AssetRegistry/AssetRegistryModule.h"
#include "Toolkit/ObjectHierarchySerializer.h"
#include "Toolkit/PropertySerializer.h"
#include "Toolkit/AssetDumping/AssetTypeSerializerMacros.h"
#include "Toolkit/AssetDumping/SerializationContext.h"

void UDataAssetSerializer::SerializeAsset(TSharedRef<FSerializationContext> Context) const {
    BEGIN_ASSET_SERIALIZATION(UDataAsset)
    
    SERIALIZE_ASSET_OBJECT
    END_ASSET_SERIALIZATION
}

FTopLevelAssetPath UDataAssetSerializer::GetAssetClass() const {
    return FTopLevelAssetPath(UDataAsset::StaticClass());
}

void UDataAssetSerializer::GetAdditionallyHandledAssetClasses(TArray<FTopLevelAssetPath>& OutExtraAssetClasses) {
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
		Filter.TagsAndValues.Add(FBlueprintTags::NativeParentClassPath, FObjectPropertyBase::GetExportPath(DerivedClass));
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
