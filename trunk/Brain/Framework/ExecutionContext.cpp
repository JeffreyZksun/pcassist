#include "StdAfx.h"
#include "ExecutionContext.h"
#include "TaskManager.h"


ExecutionContext::ExecutionContext(BrainApplication* pBrainApplication, BehaviorNode* pBehavior)
	: mpBrainApplication(pBrainApplication), mpCurrentBehavior(pBehavior)
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

BrainApplication* ExecutionContext::GetApplication() const
{
	ASSERT(mpBrainApplication != NULL);
	if(mpBrainApplication != NULL)
		return mpBrainApplication;

	return NULL;
}