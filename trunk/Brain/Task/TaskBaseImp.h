#pragma once

class ITaskSystem;

namespace Ts
{
	class TaskBase;	

	class TaskBaseImp											
	{															
	public:														
		typedef boost::shared_ptr<TaskBase>		owner_pointer;		
		typedef boost::weak_ptr<TaskBase>		owner_weak_pointer;	

	public:														
		TaskBaseImp(owner_pointer pSelf, WString taskId);							
		virtual ~TaskBaseImp();							

		owner_pointer   Self() const;	

	public:
		virtual bool            IsReady(ITaskSystem* pTaskSystem) const;
		virtual const WString&	GetId() const;
		virtual bool            Execute(ITaskSystem* pTaskSystem) = 0;

	private:													
		owner_weak_pointer			m_pSelf;

		WString						m_TaskId;
	};

}
