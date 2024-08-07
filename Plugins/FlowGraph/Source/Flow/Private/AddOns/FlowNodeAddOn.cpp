// Copyright https://github.com/MothCocoon/FlowGraph/graphs/contributors

#include "AddOns/FlowNodeAddOn.h"
#include "Nodes/FlowNode.h"

#include "Misc/RuntimeErrors.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(FlowNodeAddOn)

void UFlowNodeAddOn::InitializeInstance()
{
	CacheFlowNode();

	Super::InitializeInstance();
}

void UFlowNodeAddOn::DeinitializeInstance()
{
	Super::DeinitializeInstance();

	FlowNode = nullptr;
}

void UFlowNodeAddOn::TriggerFirstOutput(const bool bFinish)
{
	if (ensure(FlowNode))
	{
		FlowNode->TriggerFirstOutput(bFinish);
	}
}

void UFlowNodeAddOn::TriggerOutput(const FName PinName, const bool bFinish, const EFlowPinActivationType ActivationType)
{
	if (ensure(FlowNode))
	{
		FlowNode->TriggerOutput(PinName, bFinish, ActivationType);
	}
}

void UFlowNodeAddOn::Finish()
{
	if (ensure(FlowNode))
	{
		FlowNode->Finish();
	}
}

EFlowAddOnAcceptResult UFlowNodeAddOn::AcceptFlowNodeAddOnParent_Implementation(const UFlowNodeBase* ParentTemplate) const
{
	// Subclasses may override this function to opt in to parent classes
	return EFlowAddOnAcceptResult::Undetermined;
}

UFlowNode* UFlowNodeAddOn::GetFlowNode() const
{
	// We are making the assumption that this would addlways be known
	// during runtime and that we are not calling this method before the addon has been
	// initialized.
	ensure(FlowNode);

	return FlowNode;
}

bool UFlowNodeAddOn::IsSupportedInputPinName(const FName& PinName) const
{
	if (InputPins.IsEmpty())
	{
		return true;
	}

	if (const FFlowPin* FoundFlowPin = FindFlowPinByName(PinName, InputPins))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void UFlowNodeAddOn::CacheFlowNode()
{
	UObject* OuterObject = GetOuter();
	while (IsValid(OuterObject))
	{
		FlowNode = Cast<UFlowNode>(OuterObject);
		if (FlowNode)
		{
			break;
		}

		OuterObject = OuterObject->GetOuter();
	}

	ensureAsRuntimeWarning(FlowNode);
}
