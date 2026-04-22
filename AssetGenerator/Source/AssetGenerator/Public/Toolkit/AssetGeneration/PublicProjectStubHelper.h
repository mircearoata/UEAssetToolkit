#pragma once
#include "CoreMinimal.h"
#include "Animation/Skeleton.h"
#include "UObject/GCObject.h"

class ASSETGENERATOR_API FStubFileInfo {
	FString FullFilePath;
	FString FileHash;
public:
	FStubFileInfo(const FString& FileName);

	FORCEINLINE FString GetFullFilePath() const { return FullFilePath; }
	FORCEINLINE FString GetFileHash() const { return FileHash; }
};

template<typename T>
class TStubAssetInfo : public FGCObject  {
	TObjectPtr<T> Object;
public:
	FORCEINLINE TStubAssetInfo(const TCHAR* PackageName) {
		this->Object = LoadObject<T>(NULL, PackageName);
		checkf(Object, TEXT("Failed to load stub %s asset from %s"), *T::StaticClass()->GetName(), PackageName);
	}

	FORCEINLINE TObjectPtr<T> GetObject() const { return Object; }

	virtual void AddReferencedObjects(FReferenceCollector& Collector) override{
		Collector.AddReferencedObject(Object);
	}

	virtual FString GetReferencerName() const override{
		return FString::Printf(TEXT("TStubAssetInfo<%s>(%s)"), *T::StaticClass()->GetName(), Object ? *Object->GetFullName() : TEXT("N/A"));
	}
};

class ASSETGENERATOR_API FPublicProjectStubHelper {
public:
	static FString ResolveStubFilePath(const FString& Filename);

	static FStubFileInfo EditorCube;
	static FStubFileInfo DefaultTexture;
	static FStubFileInfo DefaultSkeletalMesh;
	static TStubAssetInfo<USkeleton> DefaultSkeletalMeshSkeleton;
};