#pragma once
#include "CoreMinimal.h"

#include "Engine/Font.h"
#include "Materials/MaterialLayersFunctions.h"
#include "MaterialCachedData.h"
#include "MaterialEditingLibrary.h"
#include "MaterialGraph/MaterialGraph.h"
#include "Toolkit/AssetGeneration/AssetTypeGenerator.h"
#include "MaterialGenerator.generated.h"

enum class EMaterialParameterType : uint8;
struct FMaterialCachedExpressionData;
class UMaterial;
class UFont;
class UTexture;
class URuntimeVirtualTexture;
class UMaterialParameterCollection;
class ULandscapeGrassType;
class UMaterialExpressionComment;

struct FSimpleFontParameterValue {
	TSoftObjectPtr<UFont> Font;
	int32 FontPage;

	FORCEINLINE FString ToString() const {
		return FString::Printf(TEXT("%s (Page = %d)"), *Font->GetPathName(), FontPage);
	}
};

template<typename T>
struct TMaterialParameter {
	FMaterialParameterInfo ParameterInfo;
	T ParameterValue;
};

template<typename T>
struct TParameterValueChange {
	FName ParameterName;
	T OldValue;
	T NewValue;
};

struct FMaterialLayoutChangeInfo {
	//Removed Parameters
	TArray<FMaterialParameterInfo> RemovedMaterialParameters;

	//Added parameters with their values
	TArray<TMaterialParameter<float>> NewScalarParameters;
	TArray<TMaterialParameter<FLinearColor>> NewVectorParameters;
	TArray<TMaterialParameter<TSoftObjectPtr<UTexture>>> NewTextureParameters;
	TArray<TMaterialParameter<FSimpleFontParameterValue>> NewFontParameters;
	TArray<TMaterialParameter<TSoftObjectPtr<URuntimeVirtualTexture>>> NewVirtualTextureParameters;

	//Parameter value changes
	TArray<TParameterValueChange<float>> ScalarParameterValueChanges;
	TArray<TParameterValueChange<FLinearColor>> VectorParameterValueChanges;
	TArray<TParameterValueChange<TSoftObjectPtr<UTexture>>> TextureParameterValueChanges;
	TArray<TParameterValueChange<FSimpleFontParameterValue>> FontParameterValueChanges;
	TArray<TParameterValueChange<TSoftObjectPtr<URuntimeVirtualTexture>>> VirtualTextureParameterValueChanges;

	//Texture Sampler related changes
	TArray<UMaterialParameterCollection*> NewReferencedParameterCollections;
	TArray<UMaterialParameterCollection*> RemovedParameterCollections;

	//Quality Level and Scene Color expression related booleans
	bool bAddedQualityLevelNode;
	bool bRemovedQualityLevelNode;

	bool bAddedSceneColorExpression;
	bool bRemovedSceneColorExpression;

	bool bAddedVirtualTextureOutput;
	bool bRemovedVirtualTextureOutput;

	//Grass Types being added or removed
	TArray<ULandscapeGrassType*> NewGrassTypes;
	TArray<ULandscapeGrassType*> RemovedGrassTypes;

	//Particle System Dynamic Parameters
	TArray<FName> NewDynamicParameters;
	TArray<FName> RemovedDynamicParameters;

	//Texture Sampler Changes (should be taken with grain of salt due to Texture Parameters)
	TArray<UTexture*> NewReferencedTextures;
	TArray<UTexture*> NoLongerReferencedTextures;

	bool IsEmpty() const;
	void PrintChangeReport(TArray<FString>& OutReport) const;
	bool IsParameterNodeRemoved(const FName& ParameterName);

	FORCEINLINE FMaterialLayoutChangeInfo(): bAddedQualityLevelNode(false),
											 bRemovedQualityLevelNode(false),
	                                         bAddedSceneColorExpression(false),
	                                         bRemovedSceneColorExpression(false),
	                                         bAddedVirtualTextureOutput(false),
	                                         bRemovedVirtualTextureOutput(false) {}
};

struct FIndexedParameterInfo {
	FMaterialParameterInfo ParameterInfo;
	EMaterialParameterType ParameterType;
	int32 ParameterIndex;
};

UCLASS(MinimalAPI)
class UMaterialGenerator : public UAssetTypeGenerator {
	GENERATED_BODY()
public:	
	UPROPERTY()
	FMaterialCachedParameterEntry RuntimeEntries[NumMaterialRuntimeParameterTypes];
	
protected:
	
	const FMaterialCachedParameterEntry& GetParameterTypeEntry(EMaterialParameterType Type) const { return RuntimeEntries[static_cast<int32>(Type)]; }
	
	virtual void PostInitializeAssetGenerator() override;
	virtual void CreateAssetPackage() override final;
	virtual void OnExistingPackageLoaded() override final;
	
	virtual void PopulateMaterialWithData(UMaterial* Asset, FMaterialLayoutChangeInfo& OutLayoutChangeInfo);
	virtual bool IsMaterialUpToDate(UMaterial* Asset, FMaterialLayoutChangeInfo& OutLayoutChangeInfo) const;
	
	void PopulateLayoutChangeInfoForNewMaterial(FMaterialLayoutChangeInfo& OutLayoutChangeInfo) const;
	void TryApplyMaterialLayoutChange(UMaterial* Material, FMaterialLayoutChangeInfo& LayoutChangeInfo);
	void ApplyLayoutChangelistToMaterial(UMaterial* Material, FMaterialLayoutChangeInfo& LayoutChangeInfo, bool bSoftMerge);

	void ApplyOtherLayoutChanges(UMaterial* Material, FMaterialLayoutChangeInfo& LayoutChangeInfo);
	void ApplyMaterialParameterValueChanges(UMaterial* Material, FMaterialLayoutChangeInfo& LayoutChangeInfo);
	void SpawnNewMaterialParameterNodes(UMaterial* Material, FMaterialLayoutChangeInfo& LayoutChangeInfo);
	void RemoveOutdatedMaterialLayoutNodes(UMaterial* Material, FMaterialLayoutChangeInfo& LayoutChangeInfo, bool bOnlyRemoveParameterNodes);
	static void CleanupStubMaterialNodes(UMaterial* Material);
	static void TryConnectBasicMaterialPins(UMaterial* Material);
	static void ConnectDummyParameterNodes(UMaterial* Material);
	
	static void DetectMaterialExpressionChanges(const FMaterialCachedExpressionData& OldData, const FMaterialCachedExpressionData& NewData, FMaterialLayoutChangeInfo& ChangeInfo);
	static void AddNewParameterInfo(const FMaterialCachedExpressionData& Data, int32 Index, EMaterialParameterType Type, const FMaterialParameterInfo& ParameterInfo, FMaterialLayoutChangeInfo& ChangeInfo);
	static void CompareParameterValues(const FMaterialCachedExpressionData& OldData, const FMaterialCachedExpressionData& NewData, int32 IndexOld, int32 IndexNew, EMaterialParameterType Type, FName ParameterName, FMaterialLayoutChangeInfo& ChangeInfo);

	static void CreateGeneratedMaterialComment(UMaterial* Material);
	static FString CreateMaterialChangelistCommentText(const FMaterialLayoutChangeInfo& ChangeInfo);

	static void SpawnCommentWithText(UMaterial* Material, const FString& CommentText, const FVector2D& NodePos);
	static void RemoveMaterialComment(UMaterial* Material, UMaterialExpressionComment* Comment);
	static bool IsMaterialQualityNodeUsed(const FMaterialCachedExpressionData& Data);
public:
	virtual void PopulateStageDependencies(TArray<FPackageDependency>& OutDependencies) const override;
	virtual FTopLevelAssetPath GetAssetClass() override;
	static FVector2D GetGoodPlaceForNewMaterialExpression(UMaterial* Material);
	static void ForceMaterialCompilation(UMaterial* Material);
	static void ConnectBasicParameterPinsIfPossible(UMaterial* Material, const FString& ErrorMessage);

	template<typename T>
	FORCEINLINE static T* SpawnMaterialExpression(UMaterial* Material, const FVector2D NodePos, UClass* ExpressionClass = T::StaticClass())
	{
		T* NewMaterialExpression = CastChecked<T>(UMaterialEditingLibrary::CreateMaterialExpressionEx(Material, NULL, ExpressionClass, NULL, NodePos.X, NodePos.Y));

		if (Material->MaterialGraph) {
			Material->MaterialGraph->AddExpression(NewMaterialExpression, false);
		}
		return NewMaterialExpression;
	}

	template<typename T>
	FORCEINLINE static T* SpawnMaterialExpression(UMaterial* Material, UClass* ExpressionClass = T::StaticClass())
	{
		return SpawnMaterialExpression<T>(Material, GetGoodPlaceForNewMaterialExpression(Material), ExpressionClass);
	}
};
