#pragma once
#include "CoreMinimal.h"
#include "Toolkit/AssetTypeGenerator/SimpleAssetGenerator.h"
#include "BlendSpaceGenerator.generated.h"

UCLASS(MinimalAPI)
class UBlendSpaceGenerator : public USimpleAssetGenerator {
	GENERATED_BODY()
protected:
	virtual UClass* GetAssetObjectClass() const override;
public:
	virtual void GetAdditionallyHandledAssetClasses(TArray<FTopLevelAssetPath>& OutExtraAssetClasses) override;
	virtual FTopLevelAssetPath GetAssetClass() override;
};