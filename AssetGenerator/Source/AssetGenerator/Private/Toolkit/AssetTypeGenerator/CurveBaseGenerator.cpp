#include "Toolkit/AssetTypeGenerator/CurveBaseGenerator.h"
#include "Curves/CurveFloat.h"
#include "Curves/CurveLinearColor.h"
#include "Curves/CurveVector.h"
#include "Dom/JsonObject.h"

UClass* UCurveBaseGenerator::GetAssetObjectClass() const {
	const FString AssetClassPath = GetAssetData()->GetStringField(TEXT("AssetClass"));
    return FindObjectChecked<UClass>(NULL, *AssetClassPath);
}

void UCurveBaseGenerator::GetAdditionallyHandledAssetClasses(TArray<FTopLevelAssetPath>& OutExtraAssetClasses) {
	OutExtraAssetClasses.Add(FTopLevelAssetPath(UCurveVector::StaticClass()));
	OutExtraAssetClasses.Add(FTopLevelAssetPath(UCurveFloat::StaticClass()));
	OutExtraAssetClasses.Add(FTopLevelAssetPath(UCurveLinearColor::StaticClass()));
}

FTopLevelAssetPath UCurveBaseGenerator::GetAssetClass() {
	return FTopLevelAssetPath(UCurveBase::StaticClass());
}
