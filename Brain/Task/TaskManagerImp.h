#pragma once

#include <list>
#include <map>

#include <boost/asio.hpp>
#include <boost/thread.hpp>

class ITaskSystem;

namespace Ts
{
	class TaskManager;
	class ITask;
	typedef boost::shared_ptr<ITask> ITaskPtr;

    class TaskManagerImp	
    {
	public:														
		typedef boost::shared_ptr<TaskManager>		owner_pointer;		
		typedef boost::weak_ptr<TaskManager>		owner_weak_pointer;	
		typedef std::list<ITaskPtr>					TaskList;
		typedef std::map<WString, ITaskPtr>			TaskMap;

	public:														
		TaskManagerImp(owner_pointer pSelf, ITaskSystem* pTaskSystem);							
		~TaskManagerImp();							

		owner_pointer   Self() const;

	public:
		void			Start();
		void            Stop();
		size_t          Poll(); // Execute all the ready tasks without block
		size_t          PollOne(); // Execute at most one the ready task without block

		bool			AddTask(ITaskPtr pTask);
		bool			RemoveTask(WString taskId);
		size_t			PendingTaskCount() const;

	private:
		ITaskPtr		PopReadyTask();

		void            ThreadEntry();
		void			do_set_timer();
		void			handle_timer_expires(const boost::system::error_code& error);

	private:													
		owner_weak_pointer			m_pSelf;

		ITaskSystem*				m_pTaskSystem;

		TaskList					m_PendingTaskList;
		TaskMap						m_CachedPendingTaskMap; // Improve query performance.

		bool						m_bStop;
		boost::shared_ptr<boost::thread>	m_pAsioThread;
		boost::asio::io_service				m_io_service;
		boost::asio::deadline_timer			m_timer;

    };
}