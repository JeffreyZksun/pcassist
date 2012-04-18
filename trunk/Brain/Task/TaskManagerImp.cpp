
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

bool TaskManagerImp::AddTask(const WString& taskId)
{
	RECURSIVE_LOCK_GUARD(ComponetMutexs::GetTaskManagerMutex());

	m_PendingTaskList.push_back(taskId);

	return true;
}

bool TaskManagerImp::RemoveTask(const WString& taskId)
{
	RECURSIVE_LOCK_GUARD(ComponetMutexs::GetTaskManagerMutex());

	// Remove all the tasks with the same id.
	TaskIdList::iterator it = std::find(m_PendingTaskList.begin(), m_PendingTaskList.end(), taskId);
	while(m_PendingTaskList.end() != it) // exist
	{
		m_PendingTaskList.erase(it);
		it = std::find(m_PendingTaskList.begin(), m_PendingTaskList.end(), taskId);
	}

	return true;
}

size_t TaskManagerImp::PendingTaskCount() const
{
	return m_PendingTaskList.size();
}

bool TaskManagerImp::RegisterTask(ITaskPtr pTask)
{
	if(NULL == pTask)
		return false;

	RECURSIVE_LOCK_GUARD(ComponetMutexs::GetTaskManagerMutex());

	TaskMap::iterator itMap = m_CachedRegisteredTaskMap.find(pTask->GetObjectId());
	if(itMap != m_CachedRegisteredTaskMap.end())
	{
		return false; //Avoid duplicated name.
	}

	// Append task
	m_RegisteredTaskList.push_back(pTask);
	m_CachedRegisteredTaskMap.insert(TaskMap::value_type(pTask->GetObjectId(), pTask));

	return true;
}
bool TaskManagerImp::UnregisterTask(ITaskPtr pTask)
{
	if(NULL == pTask)
		return false;

	RECURSIVE_LOCK_GUARD(ComponetMutexs::GetTaskManagerMutex());

	TaskMap::iterator itMap = m_CachedRegisteredTaskMap.find(pTask->GetObjectId());
	if(m_CachedRegisteredTaskMap.end() == itMap)
	{
		return false; // No task found.
	}

	m_RegisteredTaskList.remove(itMap->second);
	m_CachedRegisteredTaskMap.erase(itMap);
	return true;
}

size_t TaskManagerImp::RegisteredTaskCount() const
{
	return m_RegisteredTaskList.size();
}

ITaskPtr TaskManagerImp::GetTaskById(const WString& taskId) const
{
	ITaskPtr pTask;
	RECURSIVE_LOCK_GUARD(ComponetMutexs::GetTaskManagerMutex());
	TaskMap::const_iterator itMap = m_CachedRegisteredTaskMap.find(taskId);
	if(itMap != m_CachedRegisteredTaskMap.end())
		pTask = itMap->second;

	return pTask;
}

ITaskPtr TaskManagerImp::PopReadyTask()
{
	ITaskPtr pReadyTask;
	RECURSIVE_LOCK_GUARD(ComponetMutexs::GetTaskManagerMutex());

	for(TaskIdList::iterator it = m_PendingTaskList.begin(); it != m_PendingTaskList.end();)
	{
		ITaskPtr ptask = GetTaskById(*it);

		if(!ptask) // No task found.
		{
			// Remove it from pending list
			it = m_PendingTaskList.erase(it);
		}
		else
		{
			if(ptask->IsReady(m_pTaskSystem))
			{
				pReadyTask = ptask;

				m_PendingTaskList.erase(it);
				break;
			}
			else
				++it; // check the next one.
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
		// There is error when destruct the io_service.
		//DATA_ASSERT(false);
	}

	if(!m_bStop)
	{
		do_set_timer();
	}
}