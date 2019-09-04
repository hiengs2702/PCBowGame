// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProceduralMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "UObject/NoExportTypes.h"
#include "GetSkeletalMeshData.generated.h"


USTRUCT(BlueprintType)
struct FMeshDataCopy
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly)
		TArray<FVector> VerticesArray;
	UPROPERTY(BlueprintReadOnly)
		TArray<FVector> Normals;
	UPROPERTY(BlueprintReadOnly)
		TArray<FVector2D> UV;
	UPROPERTY(BlueprintReadOnly)
		TArray<int32> Tris;
	UPROPERTY(BlueprintReadOnly)
		TArray<FColor> Colors;
	UPROPERTY(BlueprintReadOnly)
		TArray<FProcMeshTangent> Tangents;
};


UCLASS()
class SKELETALMESHDATA_API UGetSkeletalMeshData : public UObject
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable/*, meta = (BlueprintInternalUseOnly = "true")*/)
		static UGetSkeletalMeshData* GetMeshData(USkeletalMeshComponent* SkeMeshComp, int32 LODIndex, FMeshDataCopy & DataOut);

	void GetDataCode(USkeletalMeshComponent* SkeMeshComp, int32 LODIndex, FMeshDataCopy& DataOut);
	
};
