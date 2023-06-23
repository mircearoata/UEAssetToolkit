#include "Toolkit/AssetTypeGenerator/Texture2DArrayGenerator.h"
#include "Engine/Texture2DArray.h"

void UTexture2DArrayGenerator::UpdateTextureSource(UTexture* Texture) {
	Texture->MipGenSettings = TMGS_NoMipmaps;
	Texture->PowerOfTwoMode = ETexturePowerOfTwoSetting::None;
	
	Super::UpdateTextureSource(Texture);
}

TSubclassOf<UTexture> UTexture2DArrayGenerator::GetTextureClass() {
	return UTexture2DArray::StaticClass();
}

FTopLevelAssetPath UTexture2DArrayGenerator::GetAssetClass() {
	return FTopLevelAssetPath(UTexture2DArray::StaticClass());
}
