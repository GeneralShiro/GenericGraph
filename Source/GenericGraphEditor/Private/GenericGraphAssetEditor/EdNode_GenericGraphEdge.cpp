#include "GenericGraphAssetEditor/EdNode_GenericGraphEdge.h"

#include "EdGraphSchema_GenericGraphEdge.h"
#include "EdGraphUtilities.h"
#include "EdGraph_GenericGraph.h"
#include "EdGraph_GenericGraphEdge.h"
#include "GenericGraphEdge.h"
#include "GenericGraphAssetEditor/EdNode_GenericGraphNode.h"

#define LOCTEXT_NAMESPACE "EdNode_GenericGraphEdge"

UEdNode_GenericGraphEdge::UEdNode_GenericGraphEdge()
{
	bCanRenameNode = true;
}

void UEdNode_GenericGraphEdge::SetEdge(UGenericGraphEdge* Edge)
{
	GenericGraphEdge = Edge;
}

void UEdNode_GenericGraphEdge::AllocateDefaultPins()
{
	UEdGraphPin* Inputs = CreatePin(EGPD_Input, TEXT("Edge"), FName(), TEXT("In"));
	Inputs->bHidden = true;
	UEdGraphPin* Outputs = CreatePin(EGPD_Output, TEXT("Edge"), FName(), TEXT("Out"));
	Outputs->bHidden = true;
}

FText UEdNode_GenericGraphEdge::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	if (GenericGraphEdge)
	{
		return GenericGraphEdge->GetNodeTitle();
	}
	return FText();
}

void UEdNode_GenericGraphEdge::PinConnectionListChanged(UEdGraphPin* Pin)
{
	if (Pin->LinkedTo.Num() == 0)
	{
		// Commit suicide; transitions must always have an input and output connection
		Modify();

		// Our parent graph will have our graph in SubGraphs so needs to be modified to record that.
		if (UEdGraph* ParentGraph = GetGraph())
		{
			ParentGraph->Modify();
		}

		DestroyNode();
	}
}

void UEdNode_GenericGraphEdge::PrepareForCopying()
{
	Super::PrepareForCopying();

	GenericGraphEdge->Rename(nullptr, this, REN_DontCreateRedirectors | REN_DoNotDirty);
	BoundGraph->Rename(nullptr, this, REN_DontCreateRedirectors | REN_DoNotDirty);
}

void UEdNode_GenericGraphEdge::PostPasteNode()
{
	if (BoundGraph == nullptr)
	{
		CreateBoundGraph();
	}

	for (UEdGraphNode* GraphNode : BoundGraph->Nodes)
	{
		GraphNode->CreateNewGuid();
		GraphNode->PostPasteNode();
		GraphNode->ReconstructNode();
	}

	Super::PostPasteNode();

	for (UEdGraphPin* Pin : Pins)
	{
		if (Pin->LinkedTo.Num() == 0)
		{
			DestroyNode();
			break;
		}
	}
}

void UEdNode_GenericGraphEdge::PostPlacedNewNode()
{
	CreateBoundGraph();
}

void UEdNode_GenericGraphEdge::DestroyNode()
{
	// BoundGraph may be shared with another graph, if so, don't remove it here
	TObjectPtr<UEdGraph> GraphToRemove = GetBoundGraph();

	BoundGraph = nullptr;
	Super::DestroyNode();

	// TODO: how to rewrite this to fit this plugin?
	/*if (GraphToRemove)
	{
		UBlueprint* Blueprint = FBlueprintEditorUtils::FindBlueprintForNodeChecked(this);
		FBlueprintEditorUtils::RemoveGraph(Blueprint, GraphToRemove, EGraphRemoveFlags::Recompile);
	}*/
}

UObject* UEdNode_GenericGraphEdge::GetJumpTargetForDoubleClick() const
{
	return BoundGraph;
}

TArray<UEdGraph*> UEdNode_GenericGraphEdge::GetSubGraphs() const
{
	TArray<UEdGraph*> SubGraphs;
	SubGraphs.Add(BoundGraph);
	return SubGraphs;
}

void UEdNode_GenericGraphEdge::CreateConnections(UEdNode_GenericGraphNode* Start, UEdNode_GenericGraphNode* End)
{
	Pins[0]->Modify();
	Pins[0]->LinkedTo.Empty();

	Start->GetOutputPin()->Modify();
	Pins[0]->MakeLinkTo(Start->GetOutputPin());

	// This to next
	Pins[1]->Modify();
	Pins[1]->LinkedTo.Empty();

	End->GetInputPin()->Modify();
	Pins[1]->MakeLinkTo(End->GetInputPin());
}

UEdNode_GenericGraphNode* UEdNode_GenericGraphEdge::GetStartNode()
{
	if (Pins[0]->LinkedTo.Num() > 0)
	{
		return Cast<UEdNode_GenericGraphNode>(Pins[0]->LinkedTo[0]->GetOwningNode());
	}
	else
	{
		return nullptr;
	}
}

UEdNode_GenericGraphNode* UEdNode_GenericGraphEdge::GetEndNode()
{
	if (Pins[1]->LinkedTo.Num() > 0)
	{
		return Cast<UEdNode_GenericGraphNode>(Pins[1]->LinkedTo[0]->GetOwningNode());
	}
	else
	{
		return nullptr;
	}
}

void UEdNode_GenericGraphEdge::CreateBoundGraph()
{
	// Create a new animation graph
	check(BoundGraph == nullptr);

	// old
	//BoundGraph = FBlueprintEditorUtils::CreateNewGraph(this, NAME_None, UAnimationTransitionGraph::StaticClass(), UAnimationTransitionSchema::StaticClass());

	// Construct a new graph
	BoundGraph = NewObject<UEdGraph>(this, UEdGraph_GenericGraphEdge::StaticClass(), NAME_None, RF_Transactional);
	BoundGraph->Schema = UEdGraphSchema_GenericGraphEdge::StaticClass();

	check(BoundGraph);

	// Find an interesting name
	//FEdGraphUtilities::RenameGraphToNameOrCloseToName(BoundGraph, TEXT("Transition"));
	BoundGraph->Rename(TEXT("Transition"), BoundGraph->GetOuter());

	// Initialize the anim graph
	const UEdGraphSchema* Schema = BoundGraph->GetSchema();
	Schema->CreateDefaultNodesForGraph(*BoundGraph);

	// Add the new graph as a child of our parent graph
	UEdGraph* ParentGraph = GetGraph();

	if (ParentGraph->SubGraphs.Find(BoundGraph) == INDEX_NONE)
	{
		ParentGraph->SubGraphs.Add(BoundGraph);
	}
}

#undef LOCTEXT_NAMESPACE

