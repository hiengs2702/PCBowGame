// Fill out your copyright notice in the Description page of Project Settings.


#include "GetSkeletalMeshData.h"
#include "Engine/Public/Rendering/SkeletalMeshRenderData.h"

UGetSkeletalMeshData* UGetSkeletalMeshData::GetMeshData(USkeletalMeshComponent* SkeMeshComp, int32 LODIndex, FMeshDataCopy& DataOut)
{
	UGetSkeletalMeshData* NewData = NewObject<UGetSkeletalMeshData>();
	NewData->GetDataCode(SkeMeshComp, LODIndex, DataOut);
	return NewData;
}

void UGetSkeletalMeshData::GetDataCode(USkeletalMeshComponent* SkeMeshComp, int32 LODIndex, FMeshDataCopy& DataOut)
{
	FSkeletalMeshRenderData* SkMeshRenderData = SkeMeshComp->GetSkeletalMeshRenderData();
	FSkeletalMeshLODRenderData& DataArray = SkMeshRenderData->LODRenderData[LODIndex];
	FSkinWeightVertexBuffer& SkinWeights = *SkeMeshComp->GetSkinWeightBuffer(LODIndex);

	int32 NumSourceVertices = DataArray.RenderSections[0].NumVertices;

	for (int32 i = 0; i < NumSourceVertices; i++)
	{
		FVector SkinnedVectorPos = USkeletalMeshComponent::GetSkinnedVertexPosition(SkeMeshComp, i, DataArray, SkinWeights);
		DataOut.VerticesArray.Add(SkinnedVectorPos);

		FVector ZTangentStatic = DataArray.StaticVertexBuffers.StaticMeshVertexBuffer.VertexTangentZ(i);
		FVector XTangentStatic = DataArray.StaticVertexBuffers.StaticMeshVertexBuffer.VertexTangentX(i);
		DataOut.Normals.Add(ZTangentStatic);
		DataOut.Tangents.Add(FProcMeshTangent(XTangentStatic, false));

		FVector2D uvs = DataArray.StaticVertexBuffers.StaticMeshVertexBuffer.GetVertexUV(i, 0);
		DataOut.UV.Add(uvs);

		DataOut.Colors.Add(FColor(0, 0, 0, 255));
	}
		
	FMultiSizeIndexContainerData indicesData;
	DataArray.MultiSizeIndexContainer.GetIndexBuffer(indicesData.Indices);
	
		
	for (int32 i = 0; i < indicesData.Indices.Num(); i++)
	{
		uint32 a = 0;
		a = indicesData.Indices[i];
		DataOut.Tris.Add(a);
	}

}
