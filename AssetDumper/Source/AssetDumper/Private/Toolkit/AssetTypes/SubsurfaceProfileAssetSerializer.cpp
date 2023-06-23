#include "Toolkit/AssetTypes/SubsurfaceProfileAssetSerializer.h"
#include "Toolkit/AssetDumping/SerializationContext.h"
#include "Toolkit/AssetDumping/AssetTypeSerializerMacros.h"
#include "Toolkit/ObjectHierarchySerializer.h"
#include "Engine/SubsurfaceProfile.h"

void USubsurfaceProfileAssetSerializer::SerializeAsset(TSharedRef<FSerializationContext> Context) const {
    BEGIN_ASSET_SERIALIZATION(USubsurfaceProfile)
        SERIALIZE_ASSET_OBJECT
    END_ASSET_SERIALIZATION
}

FTopLevelAssetPath USubsurfaceProfileAssetSerializer::GetAssetClass() const {
    return FTopLevelAssetPath(USubsurfaceProfile::StaticClass());
}
