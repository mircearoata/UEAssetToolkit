#pragma once
#include "CoreMinimal.h"
#include "SimpleAssetGenerator.h"
#include "MaterialInstanceGenerator.generated.h"

UCLASS(MinimalAPI)
class UMaterialInstanceGenerator : public USimpleAssetGenerator {
	GENERATED_BODY()
protected:
	virtual void PostInitializeAssetGenerator() override;
	virtual UClass* GetAssetObjectClass() const override;

	virtual void PopulateSimpleAssetWithData(UObject* Asset) override;
	virtual bool IsSimpleAssetUpToDate(UObject* Asset) const override;
	FStaticParameterSet GetStaticParameterOverrides() const;
public:
	virtual void PopulateStageDependencies(TArray<FPackageDependency>& OutDependencies) const override;
protected:
	virtual void PreFinishAssetGeneration() override;
	// Saves parent material packages we spawned static parameter nodes into (they were already
	// written to disk during their own generation pass, so they must be re-saved with us).
	virtual void GetAdditionalPackagesToSave(TArray<UPackage*>& OutPackages) override;
public:
	virtual FTopLevelAssetPath GetAssetClass() override;
private:
	FProperty* AssetUserDataProperty;
	// Parent material packages modified by EnsureStaticSwitchNodesPresent during DATA_POPULATION
	UPROPERTY()
	TArray<UPackage*> ModifiedParentPackages;
};
