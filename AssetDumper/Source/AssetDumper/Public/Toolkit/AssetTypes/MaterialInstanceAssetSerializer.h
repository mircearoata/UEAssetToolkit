#pragma once
#include "Toolkit/AssetDumping/AssetTypeSerializer.h"
#include "MaterialInstanceAssetSerializer.generated.h"

UCLASS(MinimalAPI)
class UMaterialInstanceAssetSerializer : public UAssetTypeSerializer {
    GENERATED_BODY()
public:
    virtual void SerializeAsset(TSharedRef<FSerializationContext> Context) const override;

    virtual FTopLevelAssetPath GetAssetClass() const override;
};
