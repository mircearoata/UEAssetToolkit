#include "Toolkit/AssetTypes/MediaPlayerAssetSerializer.h"
#include "Toolkit/AssetDumping/AssetTypeSerializerMacros.h"
#include "Toolkit/ObjectHierarchySerializer.h"
#include "Toolkit/AssetDumping/SerializationContext.h"
#include "MediaPlayer.h"

void UMediaPlayerAssetSerializer::SerializeAsset(TSharedRef<FSerializationContext> Context) const {
	BEGIN_ASSET_SERIALIZATION(UMediaPlayer)
	SERIALIZE_ASSET_OBJECT
	END_ASSET_SERIALIZATION
}

FTopLevelAssetPath UMediaPlayerAssetSerializer::GetAssetClass() const {
	return FTopLevelAssetPath(UMediaPlayer::StaticClass());
}
