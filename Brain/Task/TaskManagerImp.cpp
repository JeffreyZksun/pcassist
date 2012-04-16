
#include "stdafx.h"

#include "TaskManagerImp.h"

using namespace Ts;

TaskManagerImp::TaskManagerImp(owner_pointer pSelf, ITaskSystem* pTaskSystem)			
	: m_pSelf(pSelf), m_pTaskSystem(pTaskSystem)
{											
}

TaskManagerImp::~TaskManagerImp()
{

}

TaskManagerImp::owner_pointer TaskManagerImp::Self() const	
{											
	return m_pSelf.lock();					
}

bool TaskManagerImp::Start()
{
	// ToDo
}
void TaskManagerImp::Stop()
{
	// ToDo
}

bool TaskManagerImp::AddTask(ITaskPtr pTask)
{
	// ToDo
	return false;
}
