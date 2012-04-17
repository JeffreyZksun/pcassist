
#include "stdafx.h"

#include "TaskBaseImp.h"

using namespace Ts;

TaskBaseImp::TaskBaseImp(owner_pointer pSelf, WString taskId)			
	: m_pSelf(pSelf), m_TaskId(taskId)						
{											
}

TaskBaseImp::~TaskBaseImp()
{

}

TaskBaseImp::owner_pointer TaskBaseImp::Self() const	
{											
	return m_pSelf.lock();					
}

bool TaskBaseImp::IsReady(ITaskSystem* pTaskSystem) const
{
	if(NULL == pTaskSystem)
		return false;

	return true;
}

const WString&	TaskBaseImp::GetId() const
{
	return m_TaskId;
}
