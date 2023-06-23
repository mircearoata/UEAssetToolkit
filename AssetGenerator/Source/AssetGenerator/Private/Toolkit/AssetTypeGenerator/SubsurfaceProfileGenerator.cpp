#include "Toolkit/AssetTypeGenerator/SubsurfaceProfileGenerator.h"
#include "Engine/SubsurfaceProfile.h"

UClass* USubsurfaceProfileGenerator::GetAssetObjectClass() const {
	return USubsurfaceProfile::StaticClass();
}

FTopLevelAssetPath USubsurfaceProfileGenerator::GetAssetClass() {
	return FTopLevelAssetPath(USubsurfaceProfile::StaticClass());
}
