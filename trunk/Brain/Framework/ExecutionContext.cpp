#include "StdAfx.h"
#include "ExecutionContext.h"
#include "TaskManager.h"


ExecutionContext::ExecutionContext(BehaviorNode* pBehavior, ParameterTable* pInTable)
	: mpCurrentBehavior(pBehavior), mpInputTable(pInTable)
{

}

void ExecutionContext::SetInputParameterTable(ParameterTable* pInTable)
{
	ASSERT(pInTable != NULL);
	mpInputTable = pInTable;
}

ParameterTable* const ExecutionContext::GetInputParameterTable() const
{
	ASSERT(mpInputTable != NULL);
	return mpInputTable;
}

void ExecutionContext::SetBehaviorNode(BehaviorNode* pBehavior)
{
	ASSERT(pBehavior != NULL);
	mpCurrentBehavior = pBehavior;
}

BehaviorNode* const ExecutionContext::GetBehaviorNode() const
{
	ASSERT(mpCurrentBehavior != NULL);
	return mpCurrentBehavior;
}

BrainApplication* ExecutionContext::GetApplication() const
{
	ASSERT(mpCurrentBehavior != NULL);
	if(mpCurrentBehavior != NULL)
		return mpCurrentBehavior->GetApplication();

	return NULL;
}