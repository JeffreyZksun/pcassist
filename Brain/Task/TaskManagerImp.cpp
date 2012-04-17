
#include "stdafx.h"

#include "TaskManagerImp.h"
#include "ITask.h"
#include "ThreadLocks.h"

using namespace Ts;

// microseconds
#define TASK_INTERVAL 500

TaskManagerImp::TaskManagerImp(owner_pointer pSelf, ITaskSystem* pTaskSystem)			
	: m_pSelf(pSelf), m_pTaskSystem(pTaskSystem), m_bStop(false), m_io_service(), m_timer(m_io_service)
{											
}

TaskManagerImp::~TaskManagerImp()
{

}

TaskManagerImp::owner_pointer TaskManagerImp::Self() const	
{											
	return m_pSelf.lock();
}

void TaskManagerImp::Start()
{
	m_bStop = false;

	do_set_timer();

	// Run the asio tasks in the working thread.
	if(NULL == m_pAsioThread)
		m_pAsioThread.reset(new boost::thread(boost::bind( &TaskManagerImp::ThreadEntry, this)));
}

void TaskManagerImp::Stop()
{
	m_bStop = true;
}

size_t TaskManagerImp::Poll()
{
	size_t count = 0;

	while(PollOne() > 0)
	{
		count++;
	}

	return count;
}

size_t TaskManagerImp::PollOne()
{
	size_t count = 0;

	ITaskPtr pReadyTask = PopReadyTask();
	if(pReadyTask)
	{
		pReadyTask->Execute(m_pTaskSystem);
		count++;
	}

	return count;
}


bool TaskManagerImp::AddTask(ITaskPtr pTask)
{
	if(!pTask.get())
		return false;

	RECURSIVE_LOCK_GUARD(ComponetMutexs::GetTaskManagerMutex());

	TaskMap::iterator itMap = m_CachedPendingTaskMap.find(pTask->GetId());
	if(itMap != m_CachedPendingTaskMap.end())
	{
		return false; //Avoid duplicated name.
	}

	// Append task
	m_PendingTaskList.push_back(pTask);
	m_CachedPendingTaskMap.insert(TaskMap::value_type(pTask->GetId(), pTask));

	return true;
}

bool TaskManagerImp::RemoveTask(WString taskId)
{
	RECURSIVE_LOCK_GUARD(ComponetMutexs::GetTaskManagerMutex());

	TaskMap::iterator itMap = m_CachedPendingTaskMap.find(taskId);
	if(m_CachedPendingTaskMap.end() == itMap)
	{
		return false; // No task found.
	}

	m_PendingTaskList.remove(itMap->second);
	m_CachedPendingTaskMap.erase(itMap);
	return true;
}

size_t TaskManagerImp::PendingTaskCount() const
{
	return m_PendingTaskList.size();
}

ITaskPtr TaskManagerImp::PopReadyTask()
{

	ITaskPtr pReadyTask;
	RECURSIVE_LOCK_GUARD(ComponetMutexs::GetTaskManagerMutex());

	for(TaskList::iterator it = m_PendingTaskList.begin(); it != m_PendingTaskList.end(); ++it)
	{
		if((*it)->IsReady(m_pTaskSystem))
		{
			pReadyTask = (*it);
			RemoveTask(pReadyTask->GetId());
			break;
		}
	}

	return pReadyTask;
}

void TaskManagerImp::ThreadEntry()
{
	boost::system::error_code ec;
	m_io_service.run(ec);

	m_pAsioThread.reset();
	m_bStop = true;
}

void TaskManagerImp::do_set_timer()
{
	m_timer. expires_from_now(boost::posix_time::microseconds(TASK_INTERVAL));
	m_timer.async_wait(boost::bind(&TaskManagerImp::handle_timer_expires, this, boost::asio::placeholders::error));
}

void TaskManagerImp::handle_timer_expires(const boost::system::error_code& error)
{
	if(!error)
	{
		while(!m_bStop && PollOne() > 0);
	}
	else
	{
		// Assert
		// Why error?
	}

	if(!m_bStop)
	{
		do_set_timer();
	}
}