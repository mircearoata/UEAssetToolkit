#include "Toolkit/AssetTypes/BlendSpaceAssetSerializer.h"
#include "Animation/AimOffsetBlendSpace.h"
#include "Animation/AimOffsetBlendSpace1D.h"
#include "Animation/BlendSpace.h"
#include "Animation/BlendSpace1D.h"
#include "Toolkit/ObjectHierarchySerializer.h"
#include "Toolkit/AssetDumping/AssetTypeSerializerMacros.h"
#include "Toolkit/AssetDumping/SerializationContext.h"

void UBlendSpaceSerializer::SerializeAsset(TSharedRef<FSerializationContext> Context) const {
    BEGIN_ASSET_SERIALIZATION(UBlendSpace)
	Data->SetStringField(TEXT("AssetClass"), Asset->GetClass()->GetPathName());
    SERIALIZE_ASSET_OBJECT
    END_ASSET_SERIALIZATION
}

void UBlendSpaceSerializer::GetAdditionallyHandledAssetClasses(TArray<FTopLevelAssetPath>& OutExtraAssetClasses) {
    OutExtraAssetClasses.Add(FTopLevelAssetPath(UBlendSpace::StaticClass()));
    OutExtraAssetClasses.Add(FTopLevelAssetPath(UBlendSpace1D::StaticClass()));
    OutExtraAssetClasses.Add(FTopLevelAssetPath(UAimOffsetBlendSpace::StaticClass()));
    OutExtraAssetClasses.Add(FTopLevelAssetPath(UAimOffsetBlendSpace1D::StaticClass()));
}

FTopLevelAssetPath UBlendSpaceSerializer::GetAssetClass() const {
    return FTopLevelAssetPath(UBlendSpace::StaticClass());
}
