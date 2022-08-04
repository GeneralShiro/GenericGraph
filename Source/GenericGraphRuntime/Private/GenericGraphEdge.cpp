#include "GenericGraphEdge.h"

UGenericGraphEdge::UGenericGraphEdge()
{

}

UGenericGraphEdge::~UGenericGraphEdge()
{

}

#if WITH_EDITOR
void UGenericGraphEdge::SetNodeTitle(const FText& NewTitle)
{
	NodeTitle = NewTitle;
}
#endif // #if WITH_EDITOR