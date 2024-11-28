#include "Toolkit/AssetTypes/AnimationMontageAssetSerializer.h"
#include "Animation/AnimMontage.h"
#include "Toolkit/ObjectHierarchySerializer.h"
#include "Toolkit/PropertySerializer.h"
#include "Toolkit/AssetDumping/AssetTypeSerializerMacros.h"
#include "Toolkit/AssetDumping/SerializationContext.h"

void UAnimationMontageAssetSerializer::SerializeAsset(TSharedRef<FSerializationContext> Context) const {
    BEGIN_ASSET_SERIALIZATION(UAnimMontage)
    
    DISABLE_SERIALIZATION_RAW(UAnimSequenceBase, TEXT("RawCurveData"))
    // fgcheck(Asset->RawCurveData.FloatCurves.Num() == 0);

    SERIALIZE_ASSET_OBJECT
    END_ASSET_SERIALIZATION
}

FTopLevelAssetPath UAnimationMontageAssetSerializer::GetAssetClass() const {
    return FTopLevelAssetPath(UAnimMontage::StaticClass());
}
