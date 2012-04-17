#pragma once

#include <list>
#include "TaskBaseImp.h"

namespace Ts
{
	class ImmediateTask;	

	class ImmediateTaskImp : public TaskBaseImp												
	{															
	public:														
		typedef boost::shared_ptr<ImmediateTask>	owner_pointer;		
		typedef boost::weak_ptr<ImmediateTask>		owner_weak_pointer;	
		typedef std::list<WString>					ActionList;


	public:														
		ImmediateTaskImp(owner_pointer pSelf, const WString& taskId);							

	public:
		virtual bool            Execute(ITaskSystem* pTaskSystem);

	public:
		void					AppendAction(const WString& actionId);
		size_t					GetActionCount();

	private:
		
		ActionList							m_ActionList;

	};
}
