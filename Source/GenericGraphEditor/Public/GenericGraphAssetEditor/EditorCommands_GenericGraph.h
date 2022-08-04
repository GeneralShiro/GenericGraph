#pragma once

#include "CoreMinimal.h"

class GENERICGRAPHEDITOR_API FEditorCommands_GenericGraph : public TCommands<FEditorCommands_GenericGraph>
{
public:
	/** Constructor */
	FEditorCommands_GenericGraph()
		: TCommands<FEditorCommands_GenericGraph>("GenericGraphEditor", NSLOCTEXT("Contexts", "GenericGraphEditor", "Generic Graph Editor"), NAME_None, FEditorStyle::GetStyleSetName())
	{
	}

	TSharedPtr<FUICommandInfo> GraphSettings;
	TSharedPtr<FUICommandInfo> AutoArrange;

	// View commands
	TSharedPtr<FUICommandInfo> NavigateToParent;
	TSharedPtr<FUICommandInfo> NavigateToParentBackspace;
	TSharedPtr<FUICommandInfo> NavigateToChild;

	virtual void RegisterCommands() override;
};
