#include "Toolkit/AssetTypes/CurveLinearColorAtlasAssetSerializer.h"
#include "Toolkit/AssetTypes/TextureAssetSerializer.h"
#include "Curves/CurveLinearColorAtlas.h"
#include "Toolkit/ObjectHierarchySerializer.h"
#include "Toolkit/AssetDumping/AssetTypeSerializerMacros.h"
#include "Toolkit/AssetDumping/SerializationContext.h"

void UCurveLinearColorAtlasAssetSerializer::SerializeAsset(TSharedRef<FSerializationContext> Context) const {
    BEGIN_ASSET_SERIALIZATION(UCurveLinearColorAtlas)
    SERIALIZE_ASSET_OBJECT
    UTextureAssetSerializer::SerializeTextureData(Asset->GetPathName(), Asset->GetPlatformData(), Data, Context, false, TEXT(""));
    END_ASSET_SERIALIZATION
}

FTopLevelAssetPath UCurveLinearColorAtlasAssetSerializer::GetAssetClass() const {
    return FTopLevelAssetPath(UCurveLinearColorAtlas::StaticClass());
}
