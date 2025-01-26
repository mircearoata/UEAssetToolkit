#pragma once

#include "CoreMinimal.h"
#include "Toolkit/AssetTypeGenerator/SimpleAssetGenerator.h"
#include "AkAudioEventGenerator.generated.h"

UCLASS(MinimalAPI)
class UAkAudioEventGenerator : public USimpleAssetGenerator {
	GENERATED_BODY()
protected:
	virtual void PostInitializeAssetGenerator() override;
	virtual UClass* GetAssetObjectClass() const override;
	virtual void PopulateSimpleAssetWithData(UObject* Asset) override;
public:
	virtual FTopLevelAssetPath GetAssetClass() override;
};
