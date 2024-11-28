#include "Toolkit/AssetTypes/SkeletonAssetSerializer.h"
#include "Toolkit/AssetTypes/AssetHelper.h"
#include "Toolkit/AssetTypes/FbxMeshExporter.h"
#include "Toolkit/PropertySerializer.h"
#include "Toolkit/AssetTypes/SkeletalMeshAssetSerializer.h"
#include "Animation/Skeleton.h"
#include "Toolkit/ObjectHierarchySerializer.h"
#include "Toolkit/AssetDumping/AssetTypeSerializerMacros.h"
#include "Toolkit/AssetDumping/SerializationContext.h"

void USkeletonAssetSerializer::SerializeAsset(TSharedRef<FSerializationContext> Context) const {
    BEGIN_ASSET_SERIALIZATION(USkeleton)

	DISABLE_SERIALIZATION_RAW(USkeleton, "VirtualBoneGuid");
	DISABLE_SERIALIZATION_RAW(USkeleton, "BoneTree");
	DISABLE_SERIALIZATION_RAW(USkeleton, "VirtualBones");
    
    //Serialize reference skeleton object
    const TSharedPtr<FJsonObject> ReferenceSkeleton = MakeShareable(new FJsonObject());
    USkeletalMeshAssetSerializer::SerializeReferenceSkeleton(Asset->GetReferenceSkeleton(), ReferenceSkeleton);
    Data->SetObjectField(TEXT("ReferenceSkeleton"), ReferenceSkeleton);

	//Serialize virtual bones
	TArray<TSharedPtr<FJsonValue>> VirtualBones;
	
	for (const FVirtualBone& VirtualBone : Asset->GetVirtualBones()) {
		const TSharedPtr<FJsonObject> VirtualBoneNode = MakeShareable(new FJsonObject());

		VirtualBoneNode->SetStringField(TEXT("SourceBoneName"), VirtualBone.SourceBoneName.ToString());
		VirtualBoneNode->SetStringField(TEXT("TargetBoneName"), VirtualBone.TargetBoneName.ToString());

		VirtualBones.Add(MakeShareable(new FJsonValueObject(VirtualBoneNode)));
	}
	Data->SetArrayField(TEXT("VirtualBones"), VirtualBones);

	//Serialize bone tree translation retargeting modes
	TArray<TSharedPtr<FJsonValue>> BoneTree;

	for (int32 i = 0; i < Asset->GetReferenceSkeleton().GetRawBoneNum(); i++) {
		const EBoneTranslationRetargetingMode::Type RetargetingType = Asset->GetBoneTranslationRetargetingMode(i);
		BoneTree.Add(MakeShareable(new FJsonValueNumber((int32) RetargetingType)));
	}
	Data->SetArrayField(TEXT("BoneTree"), BoneTree);

    //Serialize animation retarget sources
	TArray<TSharedPtr<FJsonValue>> AnimRetargetSources;

	for (const TPair<FName, FReferencePose>& Pair : Asset->AnimRetargetSources) {
		TSharedRef<FJsonObject> Value = MakeShareable(new FJsonObject());
		Value->SetStringField(TEXT("PoseName"), Pair.Value.PoseName.ToString());

		TArray<TSharedPtr<FJsonValue>> ReferencePose;
		for (const FTransform& Transform : Pair.Value.ReferencePose) {
			ReferencePose.Add(MakeShareable(new FJsonValueString(Transform.ToString())));
		}
		Value->SetArrayField(TEXT("ReferencePose"), ReferencePose);
		AnimRetargetSources.Add(MakeShareable(new FJsonValueObject(Value)));
	}
    Data->SetArrayField(TEXT("AnimRetargetSources"), AnimRetargetSources);

    //Serialize normal asset data
    SERIALIZE_ASSET_OBJECT

    //Serialize skeleton itself into the fbx file
    const FString OutFbxFilename = Context->GetDumpFilePath(TEXT(""), TEXT("fbx"));
    FString OutErrorMessage;
    const bool bSuccess = FFbxMeshExporter::ExportSkeletonIntoFbxFile(Asset, OutFbxFilename, false, &OutErrorMessage);
    fgcheckf(bSuccess, TEXT("Failed to export skeleton %s: %s"), *Asset->GetPathName(), *OutErrorMessage);
    
    END_ASSET_SERIALIZATION
}

FTopLevelAssetPath USkeletonAssetSerializer::GetAssetClass() const {
    return FTopLevelAssetPath(USkeleton::StaticClass());
}

bool USkeletonAssetSerializer::SupportsParallelDumping() const {
	return false;
}
