#pragma once

#include "TaskBaseImp.h"

namespace Ts
{
	class ConditionalTask;	

	class ConditionalTaskImp  : public TaskBaseImp															
	{															
	public:														
		typedef boost::shared_ptr<ConditionalTask>		owner_pointer;		
		typedef boost::weak_ptr<ConditionalTask>		owner_weak_pointer;	

	public:														
		ConditionalTaskImp(owner_pointer pSelf, const WString& taskId, const WString& conditionName, ITaskPtr pDecoratedTask);							

		// owner_pointer   Self() const;

	public:
		virtual bool            IsReady(ITaskSystem* pTaskSystem) const;
		virtual bool            Execute(ITaskSystem* pTaskSystem);

	private:													
		WString						m_Condition;
		ITaskPtr					m_pDecoratedTask;
	};

}
