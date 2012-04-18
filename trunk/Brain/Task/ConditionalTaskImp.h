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
		ConditionalTaskImp(owner_pointer pSelf, const WString& taskId, const WString& conditionId, const WString& decoratedTaskId);							


	public:
		virtual bool            IsReady(ITaskSystem* pTaskSystem) const;

	protected:
		virtual bool            OnExecute(ITaskSystem* pTaskSystem);

	private:													
		ConditionPtr			GetCondition(ITaskSystem* pTaskSystem) const;
		ITaskPtr				GetDecoratedTask(ITaskSystem* pTaskSystem) const;
	};

}
