#pragma once
#include "Toolkit/AssetDumping/AssetTypeSerializer.h"
#include "SkeletonAssetSerializer.generated.h"

UCLASS(MinimalAPI)
class USkeletonAssetSerializer : public UAssetTypeSerializer {
    GENERATED_BODY()
public:
    virtual void SerializeAsset(TSharedRef<FSerializationContext> Context) const override;
    
    virtual FTopLevelAssetPath GetAssetClass() const override;
	virtual bool SupportsParallelDumping() const override;
};
