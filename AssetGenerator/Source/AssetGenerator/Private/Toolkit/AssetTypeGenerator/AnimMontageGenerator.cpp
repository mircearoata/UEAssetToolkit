#include "Toolkit/AssetTypeGenerator/AnimMontageGenerator.h"
#include "Animation/AnimMontage.h"

UClass* UAnimMontageGenerator::GetAssetObjectClass() const {
	return UAnimMontage::StaticClass();
}

FTopLevelAssetPath UAnimMontageGenerator::GetAssetClass() {
	return FTopLevelAssetPath(UAnimMontage::StaticClass());
}
