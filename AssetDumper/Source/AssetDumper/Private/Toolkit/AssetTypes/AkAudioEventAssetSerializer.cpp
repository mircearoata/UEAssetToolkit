#include "Toolkit/AssetTypes/AkAudioEventAssetSerializer.h"
#include "Toolkit/AssetDumping/SerializationContext.h"
#include "Toolkit/AssetDumping/AssetTypeSerializerMacros.h"
#include "Toolkit/ObjectHierarchySerializer.h"
#include "AkAudioEvent.h"

void UAkAudioEventAssetSerializer::SerializeAsset(TSharedRef<FSerializationContext> Context) const
{
	BEGIN_ASSET_SERIALIZATION(UAkAudioEvent)
		SERIALIZE_ASSET_OBJECT
	END_ASSET_SERIALIZATION
}

FTopLevelAssetPath UAkAudioEventAssetSerializer::GetAssetClass() const
{
	return FTopLevelAssetPath(UAkAudioEvent::StaticClass());
}
