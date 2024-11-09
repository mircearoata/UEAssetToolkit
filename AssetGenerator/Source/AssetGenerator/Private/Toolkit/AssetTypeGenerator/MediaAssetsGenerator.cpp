#include "Toolkit/AssetTypeGenerator/MediaAssetsGenerator.h"
#include "MediaPlayer.h"
#include "MediaTexture.h"
#include "FileMediaSource.h"
#include "Dom/JsonObject.h"

UClass* UMediaPlayerGenerator::GetAssetObjectClass() const {
	return UMediaPlayer::StaticClass();
}

FTopLevelAssetPath UMediaPlayerGenerator::GetAssetClass() {
	return FTopLevelAssetPath(UMediaPlayer::StaticClass());
}

UClass* UMediaTextureGenerator::GetAssetObjectClass() const {
	return UMediaTexture::StaticClass();
}

FTopLevelAssetPath UMediaTextureGenerator::GetAssetClass() {
	return FTopLevelAssetPath(UMediaTexture::StaticClass());
}

UClass* UFileMediaSourceGenerator::GetAssetObjectClass() const {
	return UFileMediaSource::StaticClass();
}

FTopLevelAssetPath UFileMediaSourceGenerator::GetAssetClass() {
	return FTopLevelAssetPath(UFileMediaSource::StaticClass());
}

void UFileMediaSourceGenerator::PopulateSimpleAssetWithData(UObject* Asset) {
	Super::PopulateSimpleAssetWithData(Asset);

	const FString DumpPackageName = GetAssetData()->GetStringField(TEXT("FilePath"));

	FString DumpFilePath = DumpPackageName;
	DumpFilePath.RemoveAt(0);
	const FString FullDumpFilePath = FPaths::Combine(GetRootDumpDirectory(), DumpFilePath);

	FString ResultDestFilePath;
	fgcheck(FPackageName::TryConvertLongPackageNameToFilename(DumpPackageName, ResultDestFilePath));

	if (!IsGeneratingPublicProject()) {
		IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
		PlatformFile.CopyFile(*ResultDestFilePath, *FullDumpFilePath);
	}
}
