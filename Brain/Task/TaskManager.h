#pragma once

#include "ITaskManager.h"

namespace Ts
{
	class TaskManagerImp;
	class ITaskSystem;

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
		virtual bool			Start();
		virtual void            Stop();
		virtual	bool			AddTask(ITaskPtr pTask);

	private:
		imp_pointer				m_pImp;
    };
}