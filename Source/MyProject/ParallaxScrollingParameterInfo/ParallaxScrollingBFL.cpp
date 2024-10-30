#include "ParallaxScrollingBFL.h"
#include "Materials/MaterialInstanceDynamic.h"

TArray<FMyParallaxStruct> UParallaxScrollingBFL::CreateLayerOffsetArray(UMaterialInstanceDynamic* MaterialInstanceDynamic, float OffsetTime)
{
	int32 Index = 0;
	float Offset = 1.0f;
	TArray<FMyParallaxStruct> ScalarParameterInfo;
	TArray<FMaterialParameterInfo> Parameters;
	TArray<FMaterialParameterInfo> OutParameterInfo;
	TArray<FGuid> OutParameterIds;
	
	MaterialInstanceDynamic->GetAllScalarParameterInfo(OutParameterInfo, OutParameterIds);
	
	for (const FMaterialParameterInfo& Param : OutParameterInfo)
	{
		Offset = Index != 0 ? Offset * 2 : Offset;
		FMyParallaxStruct NewInfo;
		NewInfo.LayerName = Param.Name;
		NewInfo.OffsetValue = Index != 0 ? OffsetTime * Offset * 0.05f : OffsetTime;

		ScalarParameterInfo.Add(NewInfo);
		Index++;
	}

	return ScalarParameterInfo;
}
