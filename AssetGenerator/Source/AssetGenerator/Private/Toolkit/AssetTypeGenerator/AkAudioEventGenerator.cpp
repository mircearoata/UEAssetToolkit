#include "Toolkit/AssetTypeGenerator/AkAudioEventGenerator.h"
#include "AkAudioEvent.h"
#include "Toolkit/PropertySerializer.h"
#include "Toolkit/AssetDumping/AssetTypeSerializerMacros.h"

void UAkAudioEventGenerator::PostInitializeAssetGenerator()
{
	UPropertySerializer* Serializer = GetPropertySerializer();

	//transient and changed every time material parameter collection is changed
	//DISABLE_SERIALIZATION(UMaterialParameterCollection, StateId);
}

UClass* UAkAudioEventGenerator::GetAssetObjectClass() const
{
	return UAkAudioEvent::StaticClass();
}

void UAkAudioEventGenerator::PopulateSimpleAssetWithData(UObject* Asset)
{
	Super::PopulateSimpleAssetWithData(Asset);
	UAkAudioEvent* AkAudioEvent = CastChecked<UAkAudioEvent>(Asset);

	AkAudioEvent->PostLoad();
}

FTopLevelAssetPath UAkAudioEventGenerator::GetAssetClass()
{
	return FTopLevelAssetPath(UAkAudioEvent::StaticClass());
}
