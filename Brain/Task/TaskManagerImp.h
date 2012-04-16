#pragma once


namespace Ts
{
	class TaskManager;
	class ITaskSystem;
	class ITask;
	typedef boost::shared_ptr<ITask> ITaskPtr;

    class TaskManagerImp	
    {
	public:														
		typedef boost::shared_ptr<TaskManager>		owner_pointer;		
		typedef boost::weak_ptr<TaskManager>		owner_weak_pointer;	

	public:														
		TaskManagerImp(owner_pointer pSelf, ITaskSystem* pTaskSystem);							
		~TaskManagerImp();							

		owner_pointer   Self() const;

	public:
		bool			Start();
		void            Stop();
		bool			AddTask(ITaskPtr pTask);

	private:													
		owner_weak_pointer			m_pSelf;

		ITaskSystem*				m_pTaskSystem;
    };
}