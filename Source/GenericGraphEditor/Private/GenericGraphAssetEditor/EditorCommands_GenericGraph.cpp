#include "GenericGraphAssetEditor/EditorCommands_GenericGraph.h"

#define LOCTEXT_NAMESPACE "EditorCommands_GenericGraph"

void FEditorCommands_GenericGraph::RegisterCommands()
{
	UI_COMMAND(GraphSettings, "Graph Settings", "Graph Settings", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(AutoArrange, "Auto Arrange", "Auto Arrange", EUserInterfaceActionType::Button, FInputChord());

	// View commands
	UI_COMMAND(NavigateToParent, "Go to parent graph", "Open the parent graph", EUserInterfaceActionType::Button, FInputChord(EKeys::PageUp));
	UI_COMMAND(NavigateToParentBackspace, "Go to parent graph", "Open the parent graph", EUserInterfaceActionType::Button, FInputChord(EKeys::BackSpace));
	UI_COMMAND(NavigateToChild, "Go to child graph", "Open the child graph", EUserInterfaceActionType::Button, FInputChord(EKeys::PageDown));

}

#undef LOCTEXT_NAMESPACE
