#include "Toolkit/AssetTypeGenerator/LandscapeGrassTypeGenerator.h"
#include "LandscapeGrassType.h"

UClass* ULandscapeGrassTypeGenerator::GetAssetObjectClass() const {
	return ULandscapeGrassType::StaticClass();
}

FTopLevelAssetPath ULandscapeGrassTypeGenerator::GetAssetClass() {
	return FTopLevelAssetPath(ULandscapeGrassType::StaticClass());
}
