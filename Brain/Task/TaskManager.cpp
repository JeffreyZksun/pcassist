
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

void TaskManager::Start()
{
	m_pImp->Start();
}
void TaskManager::Stop()
{
	m_pImp->Stop();
}

bool TaskManager::AddTask(ITaskPtr pTask)
{
	return m_pImp->AddTask(pTask);
}

size_t TaskManager::Poll()
{
	return m_pImp->Poll();
}

size_t TaskManager::PollOne()
{
	return m_pImp->PollOne();
}

bool TaskManager::RemoveTask(WString taskName)
{
	return m_pImp->RemoveTask(taskName);
}

bool TaskManager::HasPendingTask() const
{
	return m_pImp->HasPendingTask();
}