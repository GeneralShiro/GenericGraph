// Zach Ginn - https://github.com/GeneralShiro

#pragma once

#include "CoreMinimal.h"
#include "Binding/DynamicPropertyPath.h"
#include "Classes/GenericEdgeNode_Base.h"
#include "GenericEdgeNode_PropertyGetter.generated.h"

/**
 *
 */
UCLASS()
class GENERICGRAPHRUNTIME_API UGenericEdgeNode_PropertyGetter : public UGenericEdgeNode_Base
{
	GENERATED_BODY()

public:
	UPROPERTY()
		TWeakObjectPtr<UObject> SourceObject;

	UPROPERTY()
		FDynamicPropertyPath SourcePath;

public:

	UGenericEdgeNode_PropertyGetter();
};
