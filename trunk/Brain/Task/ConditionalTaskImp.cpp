
#include "stdafx.h"

#include "ConditionalTask.h"
#include "ConditionalTaskImp.h"
#include "BehaviorManager.h"
#include "ITaskSystem.h"

using namespace Ts;

ConditionalTaskImp::ConditionalTaskImp(owner_pointer pSelf, const WString& taskId, const WString& conditionName, ITaskPtr pDecoratedTask)			
	: TaskBaseImp(pSelf, taskId), m_Condition(conditionName), m_pDecoratedTask(pDecoratedTask)				
{											
}											
//
//ConditionalTaskImp::owner_pointer ConditionalTaskImp::Self() const	
//{											
//	ConditionalTaskImp::owner_pointer pSelf = boost::dynamic_pointer_cast<ConditionalTask>(TaskBaseImp::Self());
//	return pSelf;			
//}

bool ConditionalTaskImp::IsReady(ITaskSystem* pTaskSystem) const
{
	if(!m_pDecoratedTask)
		return false;

	if(NULL == pTaskSystem)
		return false;

	BehaviorManager* pBehaviorManager = pTaskSystem->GetBehaviorManager();
	if(NULL == pBehaviorManager)
		return false;

	Condition* pCondition = pBehaviorManager->GetConditionById(m_Condition.data());
	if(NULL == pCondition)
		return false;

	// ToDo disable log.
	if(!pCondition->IsTrue())
		return false;

	return m_pDecoratedTask->IsReady(pTaskSystem);
}

bool ConditionalTaskImp::Execute(ITaskSystem* pTaskSystem)
{
	if(!m_pDecoratedTask)
		return false;

	if(NULL == pTaskSystem)
		return false;

	if(IsReady(pTaskSystem))
		return m_pDecoratedTask->Execute(pTaskSystem);

	return false;
}
