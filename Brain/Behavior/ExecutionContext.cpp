#include "StdAfx.h"
#include "ExecutionContext.h"
#include "BehaviorManager.h"


ExecutionContext::ExecutionContext(TaskSystem* pTaskSystem, BehaviorNode* pBehavior)
	: mpTaskSystem(pTaskSystem), mpCurrentBehavior(pBehavior)
{

}

const ParameterTable* const ExecutionContext::GetInputParameterTable() const
{
	DATA_ASSERT(mpCurrentBehavior != NULL);
	if(mpCurrentBehavior != NULL)
		return &(mpCurrentBehavior->GetParameterTable());

	return NULL;
}

void ExecutionContext::SetBehaviorNode(BehaviorNode* pBehavior)
{
	DATA_ASSERT(pBehavior != NULL);
	mpCurrentBehavior = pBehavior;
}

BehaviorNode* const ExecutionContext::GetBehaviorNode() const
{
	DATA_ASSERT(mpCurrentBehavior != NULL);
	return mpCurrentBehavior;
}

TaskSystem* ExecutionContext::GetTaskSystem() const
{
	DATA_ASSERT(mpTaskSystem != NULL);
	if(mpTaskSystem != NULL)
		return mpTaskSystem;

	return NULL;
}