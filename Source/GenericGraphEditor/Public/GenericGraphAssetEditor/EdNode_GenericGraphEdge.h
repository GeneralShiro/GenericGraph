#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphNode.h"
#include "EdNode_GenericGraphEdge.generated.h"

class UGenericGraphNode;
class UGenericGraphEdge;
class UEdNode_GenericGraphNode;
class UEdGraph;

UCLASS(MinimalAPI)
class UEdNode_GenericGraphEdge : public UEdGraphNode
{
	GENERATED_BODY()

public:
	UPROPERTY()
		TObjectPtr<UEdGraph> OwnerGraph;

	UPROPERTY(VisibleAnywhere, Instanced, Category = "GenericGraph")
		TObjectPtr<UGenericGraphEdge> GenericGraphEdge;

protected:
	// The transition logic graph for this transition (returning a boolean)
	UPROPERTY()
		TObjectPtr<UEdGraph> BoundGraph;

	UPROPERTY(EditAnywhere, Category = "GenericGraph")
		int32 Priority;

public:
	UEdNode_GenericGraphEdge();

	void SetEdge(UGenericGraphEdge* Edge);

	//~ Begin UEdGraphNode Interface
	virtual void AllocateDefaultPins() override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual void PinConnectionListChanged(UEdGraphPin* Pin) override;
	virtual void PrepareForCopying() override;
	virtual void DestroyNode() override;
	virtual UObject* GetJumpTargetForDoubleClick() const override;
	virtual TArray<UEdGraph*> GetSubGraphs() const override;
	//~ End UEdGraphNode Interface

	virtual UEdGraphPin* GetInputPin() const { return Pins[0]; }
	virtual UEdGraphPin* GetOutputPin() const { return Pins[1]; }

	void CreateConnections(UEdNode_GenericGraphNode* Start, UEdNode_GenericGraphNode* End);
	UEdNode_GenericGraphNode* GetStartNode();
	UEdNode_GenericGraphNode* GetEndNode();

	TObjectPtr<UEdGraph> GetBoundGraph() const { return BoundGraph; }

protected:
	void CreateBoundGraph();
};
