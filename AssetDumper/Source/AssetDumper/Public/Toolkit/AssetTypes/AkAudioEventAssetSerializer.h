#pragma once

#include "CoreMinimal.h"
#include "Toolkit/AssetDumping/AssetTypeSerializer.h"
#include "AkAudioEventAssetSerializer.generated.h"

UCLASS(MinimalAPI)
class UAkAudioEventAssetSerializer : public UAssetTypeSerializer {
	GENERATED_BODY()
public:
	virtual void SerializeAsset(TSharedRef<FSerializationContext> Context) const override;

	virtual FTopLevelAssetPath GetAssetClass() const override;
};
