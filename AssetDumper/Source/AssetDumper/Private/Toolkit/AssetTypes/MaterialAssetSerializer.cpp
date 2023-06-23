#pragma once
#include "Toolkit/AssetTypes/MaterialAssetSerializer.h"
#include "Toolkit/ObjectHierarchySerializer.h"
#include "Toolkit/PropertySerializer.h"
#include "Toolkit/AssetDumping/AssetTypeSerializerMacros.h"
#include "Toolkit/AssetDumping/SerializationContext.h"
#include "AssetDumperModule.h"
#include "MaterialCachedData.h"

void UMaterialAssetSerializer::SerializeAsset(TSharedRef<FSerializationContext> Context) const {
    BEGIN_ASSET_SERIALIZATION(UMaterial)
	
    //TODO we do not serialize shaders yet, but information exposed by normal object serialization should be enough for reasonable stubs
    //obviously they will be unable to show material in editor, but they can be used to reference it and even create new instances on top of it

	DisableMaterialFunctionSerialization(Serializer);
	SerializeReferencedFunctions(Asset->GetCachedExpressionData(), Data);

	TArray<int32> ReferencedSubobjects;
	TSharedRef<FJsonObject> CachedExpressionData = ObjectSerializer->GetPropertySerializer()->SerializeStruct(StaticStruct<FMaterialCachedExpressionData>(), &Asset->GetCachedExpressionData(), &ReferencedSubobjects);
	Data->SetObjectField(TEXT("CachedExpressionData"), CachedExpressionData);
	
	TArray<TSharedPtr<FJsonValue>> ReferencedSubobjectsArray;
	for (const int32 ObjectIndex : ReferencedSubobjects) {
		ReferencedSubobjectsArray.Add(MakeShareable(new FJsonValueNumber(ObjectIndex)));
	}
	Data->SetArrayField(TEXT("ReferencedObjects"), ReferencedSubobjectsArray);
	
	SERIALIZE_ASSET_OBJECT
	
    END_ASSET_SERIALIZATION
}

void UMaterialAssetSerializer::SerializeReferencedFunctions(const FMaterialCachedExpressionData& ExpressionData, const TSharedPtr<FJsonObject> Data) {
	
	TArray<TSharedPtr<FJsonValue>> ReferencedFunctions;
	for (const FMaterialFunctionInfo& FunctionInfo : ExpressionData.FunctionInfos) {
		ReferencedFunctions.Add(MakeShareable(new FJsonValueString(FunctionInfo.Function->GetPathName())));
	}

	TArray<TSharedPtr<FJsonValue>> MaterialLayers;
	for (UMaterialFunctionInterface* Function : ExpressionData.MaterialLayers.Layers) {
		MaterialLayers.Add(MakeShareable(new FJsonValueString(Function->GetPathName())));
	}

	TArray<TSharedPtr<FJsonValue>> MaterialLayerBlends;
	for (UMaterialFunctionInterface* Function : ExpressionData.MaterialLayers.Blends) {
		MaterialLayerBlends.Add(MakeShareable(new FJsonValueString(Function->GetPathName())));
	}

	Data->SetArrayField(TEXT("ReferencedFunctions"), ReferencedFunctions);
	Data->SetArrayField(TEXT("MaterialLayers"), MaterialLayers);
	Data->SetArrayField(TEXT("MaterialLayerBlends"), MaterialLayerBlends);
}

void UMaterialAssetSerializer::DisableMaterialFunctionSerialization(UPropertySerializer* Serializer) {
	DISABLE_SERIALIZATION(FMaterialCachedExpressionData, FunctionInfos);
	DISABLE_SERIALIZATION(FMaterialCachedExpressionData, MaterialLayers);
}

FTopLevelAssetPath UMaterialAssetSerializer::GetAssetClass() const {
    return FTopLevelAssetPath(UMaterial::StaticClass());
}
