
#include "stdafx.h"

#include "TaskManager.h"
#include "TaskManagerImp.h"

using namespace Ts;

TaskManager::TaskManager()
{

}

TaskManager::~TaskManager()
{

};

TaskManager::pointer TaskManager::Create(ITaskSystem* pTaskSystem)					
{											
	TaskManager::pointer pNewObj(new TaskManager());
	TaskManager::imp_pointer pImp(new TaskManagerImp(pNewObj, pTaskSystem));
	pNewObj->m_pImp = pImp;

	return pNewObj;							
}

bool TaskManager::Start()
{
	return m_pImp->Start();
}
void TaskManager::Stop()
{
	m_pImp->Stop();
}

bool TaskManager::AddTask(ITaskPtr pTask)
{
	return m_pImp->AddTask(pTask);
}