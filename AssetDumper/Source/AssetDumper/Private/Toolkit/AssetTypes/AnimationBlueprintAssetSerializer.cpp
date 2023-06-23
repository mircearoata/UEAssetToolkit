#include "Toolkit/AssetTypes/AnimationBlueprintAssetSerializer.h"

#include "Animation/AnimBlueprint.h"
#include "Animation/AnimBlueprintGeneratedClass.h"
#include "Toolkit/ObjectHierarchySerializer.h"
#include "Toolkit/PropertySerializer.h"
#include "Toolkit/AssetDumping/AssetTypeSerializerMacros.h"
#include "Toolkit/AssetDumping/SerializationContext.h"

void UAnimationBlueprintAssetSerializer::SerializeAsset(TSharedRef<FSerializationContext> Context) const {
    BEGIN_ASSET_SERIALIZATION_BP(UAnimBlueprintGeneratedClass)
    END_ASSET_SERIALIZATION
}

FTopLevelAssetPath UAnimationBlueprintAssetSerializer::GetAssetClass() const {
    return FTopLevelAssetPath(UAnimBlueprint::StaticClass());
}
