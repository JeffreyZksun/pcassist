#pragma once

#include "TaskBase.h"

namespace Ts
{
	class ImmediateTaskImp;	

	class ImmediateTask : public TaskBase								
	{													
	public:												
		typedef boost::shared_ptr<ImmediateTask>	pointer;	
		typedef boost::shared_ptr<ImmediateTaskImp>	imp_pointer;

	public:			
		virtual ~ImmediateTask();
		static pointer		Create(const WString& taskId);
	public:
		void				AppendAction(const WString& actionId);
		size_t				GetActionCount();

	protected:											
		ImmediateTask();											

	private:											

	};

}
