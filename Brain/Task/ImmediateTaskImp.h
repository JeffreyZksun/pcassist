#pragma once

#include "TaskBaseImp.h"

namespace Ts
{
	class ImmediateTask;	

	class ImmediateTaskImp : public TaskBaseImp												
	{															
	public:														
		typedef boost::shared_ptr<ImmediateTask>	owner_pointer;		
		typedef boost::weak_ptr<ImmediateTask>		owner_weak_pointer;	

	public:														
		ImmediateTaskImp(owner_pointer pSelf, const WString& taskName);							

	public:
		virtual bool            Execute(ITaskSystem* pTaskSystem);

	private:
		// ToDo Task list
	};
}
