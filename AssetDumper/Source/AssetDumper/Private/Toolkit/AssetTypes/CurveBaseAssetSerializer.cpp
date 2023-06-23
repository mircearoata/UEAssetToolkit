#include "Toolkit/AssetTypes/CurveBaseAssetSerializer.h"
#include "Curves/CurveBase.h"
#include "Curves/CurveLinearColor.h"
#include "Curves/CurveVector.h"
#include "Toolkit/ObjectHierarchySerializer.h"
#include "Toolkit/AssetDumping/AssetTypeSerializerMacros.h"
#include "Toolkit/AssetDumping/SerializationContext.h"

void UCurveBaseAssetSerializer::SerializeAsset(TSharedRef<FSerializationContext> Context) const {
    BEGIN_ASSET_SERIALIZATION(UCurveBase)
	Data->SetStringField(TEXT("AssetClass"), Asset->GetClass()->GetPathName());
    SERIALIZE_ASSET_OBJECT
    END_ASSET_SERIALIZATION
}

void UCurveBaseAssetSerializer::GetAdditionallyHandledAssetClasses(TArray<FTopLevelAssetPath>& OutExtraAssetClasses) {
    OutExtraAssetClasses.Add(FTopLevelAssetPath(UCurveVector::StaticClass()));
    OutExtraAssetClasses.Add(FTopLevelAssetPath(UCurveFloat::StaticClass()));
    OutExtraAssetClasses.Add(FTopLevelAssetPath(UCurveLinearColor::StaticClass()));
}

FTopLevelAssetPath UCurveBaseAssetSerializer::GetAssetClass() const {
    return FTopLevelAssetPath(UCurveBase::StaticClass());
}
