#pragma once
#include "Toolkit/AssetDumping/AssetTypeSerializer.h"
#include "DataAssetSerializer.generated.h"

UCLASS(MinimalAPI)
class UDataAssetSerializer : public UAssetTypeSerializer {
    GENERATED_BODY()
public:
    virtual void SerializeAsset(TSharedRef<FSerializationContext> Context) const override;

    virtual FTopLevelAssetPath GetAssetClass() const override;
    virtual void GetAdditionallyHandledAssetClasses(TArray<FTopLevelAssetPath>& OutExtraAssetClasses) override;
};
