// Zach Ginn - https://github.com/GeneralShiro

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraph.h"
#include "EdGraph_GenericGraphEdge.generated.h"

class UEdgeGraphNode_Result;

/**
 * EdGraph class for bound graph on an edge node in a Generic Graph asset.
 */
UCLASS(MinimalAPI)
class UEdGraph_GenericGraphEdge : public UEdGraph
{
	GENERATED_BODY()

		UPROPERTY()
		TObjectPtr<UEdgeGraphNode_Result> MyResultNode;


	GENERICGRAPHEDITOR_API TObjectPtr<UEdgeGraphNode_Result> GetResultNode() { return MyResultNode; }
};
