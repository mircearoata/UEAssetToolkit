#include "Toolkit/AssetTypeGenerator/PhysicalMaterialGenerator.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Dom/JsonObject.h"

UClass* UPhysicalMaterialGenerator::GetAssetObjectClass() const {
	return UPhysicalMaterial::StaticClass();
}

FTopLevelAssetPath UPhysicalMaterialGenerator::GetAssetClass() {
	return FTopLevelAssetPath(UPhysicalMaterial::StaticClass());
}

//UClass* UPhysicalMaterialGenerator::GetAssetObjectClass() const {
//	const FString AssetClassPath = GetAssetData()->GetStringField(TEXT("AssetClass"));
//	return FindObjectChecked<UClass>(NULL, *AssetClassPath);
//}
//
//FName UPhysicalMaterialGenerator::GetAssetClass() {
//	return FTopLevelAssetPath(UPhysicalMaterial::StaticClass());
//}