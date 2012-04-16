
#include "stdafx.h"

#include "ConditionalTask.h"
#include "ConditionalTaskImp.h"

using namespace Ts;

ConditionalTaskImp::ConditionalTaskImp(owner_pointer pSelf, const WString& taskName, const WString& conditionName, const WString& decoratedTaskName)			
	: TaskBaseImp(pSelf, taskName), m_Condition(conditionName), m_DecoratedTaskName(decoratedTaskName)				
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
	if(NULL == pTaskSystem)
		return false;

	return true;
}

bool ConditionalTaskImp::Execute(ITaskSystem* pTaskSystem)
{
	if(NULL == pTaskSystem)
		return false;

	// Todo
	return false;
}
