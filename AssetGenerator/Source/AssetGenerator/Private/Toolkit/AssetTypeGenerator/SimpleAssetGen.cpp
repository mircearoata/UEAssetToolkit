#include "Toolkit/AssetTypeGenerator/SimpleAssetGen.h"
#include "Dom/JsonObject.h"

UClass* USimpleAssetGen::GetAssetObjectClass() const {
	const FString AssetClassPath = GetAssetData()->GetStringField(TEXT("AssetClass"));
	return FindObjectChecked<UClass>(NULL, *AssetClassPath);
}

FTopLevelAssetPath USimpleAssetGen::GetAssetClass() {
	return nullptr;
}

void USimpleAssetGen::PopulateStageDependencies(TArray<FPackageDependency>& OutDependencies) const {
	if (!GetAssetData()->HasField(TEXT("SkipDependencies")) || !GetAssetData()->GetBoolField(TEXT("SkipDependencies"))) {
		if (GetCurrentStage() == EAssetGenerationStage::CONSTRUCTION) {
			PopulateReferencedObjectsDependencies(OutDependencies);
		}
	}
}