#pragma once

#include "TaskBase.h"

namespace Ts
{
	class ImmediateTaskImp;	

	class ImmediateTask : public TaskBase								
	{													
	public:												
		typedef boost::shared_ptr<ImmediateTask>	pointer;		

	public:			
		virtual ~ImmediateTask();
		static pointer		Create(const WString& taskName);
	public:

	protected:											
		ImmediateTask();											

	private:											

	};

}
