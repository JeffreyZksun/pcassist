#include "StdAfx.h"
#include "ExecutionContext.h"
#include "BehaviorManager.h"


ExecutionContext::ExecutionContext(TaskSystem* pTaskSystem, BehaviorNode* pBehavior)
	: mpTaskSystem(pTaskSystem), mpCurrentBehavior(pBehavior)
{

}

const ParameterTable* const ExecutionContext::GetInputParameterTable() const
{
	ASSERT(mpCurrentBehavior != NULL);
	if(mpCurrentBehavior != NULL)
		return &(mpCurrentBehavior->GetParameterTable());

	return NULL;
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

TaskSystem* ExecutionContext::GetTaskSystem() const
{
	ASSERT(mpTaskSystem != NULL);
	if(mpTaskSystem != NULL)
		return mpTaskSystem;

	return NULL;
}