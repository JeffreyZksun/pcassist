
#include "stdafx.h"

#include "TaskManager.h"
#include "TaskManagerImp.h"

using namespace Ts;

TaskManager::TaskManager()
{

}

TaskManager::~TaskManager()
{

}

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

size_t TaskManager::Poll()
{
	return m_pImp->Poll();
}

size_t TaskManager::PollOne()
{
	return m_pImp->PollOne();
}

bool TaskManager::AddTask(const WString& taskId)
{
	return m_pImp->AddTask(taskId);
}

bool TaskManager::RemoveTask(const WString& taskId)
{
	return m_pImp->RemoveTask(taskId);
}

size_t TaskManager::PendingTaskCount() const
{
	return m_pImp->PendingTaskCount();
}

bool TaskManager::RegisterTask(ITaskPtr pTask)
{
	return m_pImp->RegisterTask(pTask);
}

bool TaskManager::UnregisterTask(ITaskPtr pTask)
{
	return m_pImp->UnregisterTask(pTask);
}

size_t TaskManager::RegisteredTaskCount() const
{
	return m_pImp->RegisteredTaskCount();
}

ITaskPtr TaskManager::GetTaskById(const WString& taskId) const
{
	return m_pImp->GetTaskById(taskId);
}
