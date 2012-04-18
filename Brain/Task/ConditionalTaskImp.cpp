
#include "stdafx.h"

#include "ConditionalTask.h"
#include "ConditionalTaskImp.h"
#include "BehaviorManager.h"
#include "ITaskSystem.h"
#include "ITaskManager.h"

using namespace Ts;

ConditionalTaskImp::ConditionalTaskImp(owner_pointer pSelf, const WString& taskId, const WString& conditionId, const WString& decoratedTaskId)			
	: TaskBaseImp(pSelf, taskId)			
{
	GetParameterTable().AddParameter(Parameter(CONDITION_ID, conditionId.data()));
	GetParameterTable().AddParameter(Parameter(DECORATED_TASK_ID, decoratedTaskId.data()));
}											

bool ConditionalTaskImp::IsReady(ITaskSystem* pTaskSystem) const
{
	if(NULL == pTaskSystem)
		return false;

	ConditionPtr pCondition = GetCondition(pTaskSystem);
	if(NULL == pCondition)
		return false;

	// ToDo disable log.
	if(!pCondition->IsTrue())
		return false;

	ITaskPtr pDecoratedTask = GetDecoratedTask(pTaskSystem);
	if(NULL == pDecoratedTask) // not registered
		return false;

	return pDecoratedTask->IsReady(pTaskSystem);
}

bool ConditionalTaskImp::OnExecute(ITaskSystem* pTaskSystem)
{
	if(NULL == pTaskSystem)
		return false;

	ITaskPtr pDecoratedTask = GetDecoratedTask(pTaskSystem);
	if(NULL == pDecoratedTask) // not registered
		return false;

	if(IsReady(pTaskSystem))
		return pDecoratedTask->Execute(pTaskSystem);

	return false;
}

ConditionPtr ConditionalTaskImp::GetCondition(ITaskSystem* pTaskSystem) const
{
	if(NULL == pTaskSystem)
		return ConditionPtr();

	BehaviorManager* pBehaviorManager = pTaskSystem->GetBehaviorManager();
	if(NULL == pBehaviorManager)
		return ConditionPtr();

	const Parameter* pPara = GetParameterTable().GetParameter(CONDITION_ID);
	if(!pPara)
		return ConditionPtr();

	return pBehaviorManager->GetConditionById(pPara->GetRawValue());
}

ITaskPtr ConditionalTaskImp::GetDecoratedTask(ITaskSystem* pTaskSystem) const
{
	if(NULL == pTaskSystem)
		return ITaskPtr();

	ITaskManagerPtr pTaskManager = pTaskSystem->GetTaskManager();
	if(NULL == pTaskManager)
		return ITaskPtr();

	const Parameter* pPara = GetParameterTable().GetParameter(DECORATED_TASK_ID);
	if(!pPara)
		return ITaskPtr();

	return pTaskManager->GetTaskById(WString(pPara->GetRawValue()));
}
