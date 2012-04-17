#pragma once

#include "ITaskManager.h"

class ITaskSystem;

namespace Ts
{
	class TaskManagerImp;

    class TaskManager : public ITaskManager	
    {
	public:												
		typedef boost::shared_ptr<TaskManager>		pointer;		
		typedef boost::shared_ptr<TaskManagerImp>	imp_pointer;

    public:
        virtual ~TaskManager(void);
		static pointer			Create(ITaskSystem* pTaskSystem);

	protected:
		TaskManager();

	public:
		virtual void			Start();
		virtual void            Stop();
		virtual	size_t          Poll(); // Execute all the ready tasks without block
		virtual	size_t          PollOne(); // Execute at most one the ready task without block

		virtual	bool			AddTask(ITaskPtr pTask);
		virtual	bool			RemoveTask(WString taskId);
		virtual	size_t			PendingTaskCount() const;

	private:
		imp_pointer				m_pImp;
    };
}