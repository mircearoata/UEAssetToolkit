#include "Toolkit/AssetTypeGenerator/BlendSpaceGenerator.h"
#include "Animation/AimOffsetBlendSpace.h"
#include "Animation/AimOffsetBlendSpace1D.h"
#include "Animation/BlendSpace.h"
#include "Dom/JsonObject.h"

UClass* UBlendSpaceGenerator::GetAssetObjectClass() const {
	const FString AssetClassPath = GetAssetData()->GetStringField(TEXT("AssetClass"));
	return FindObjectChecked<UClass>(NULL, *AssetClassPath);
}

void UBlendSpaceGenerator::GetAdditionallyHandledAssetClasses(TArray<FTopLevelAssetPath>& OutExtraAssetClasses) {
	OutExtraAssetClasses.Add(FTopLevelAssetPath(UBlendSpace::StaticClass()));
	OutExtraAssetClasses.Add(FTopLevelAssetPath(UBlendSpace1D::StaticClass()));
	OutExtraAssetClasses.Add(FTopLevelAssetPath(UAimOffsetBlendSpace::StaticClass()));
	OutExtraAssetClasses.Add(FTopLevelAssetPath(UAimOffsetBlendSpace1D::StaticClass()));
}

FTopLevelAssetPath UBlendSpaceGenerator::GetAssetClass() {
	return FTopLevelAssetPath(UBlendSpace::StaticClass());
}