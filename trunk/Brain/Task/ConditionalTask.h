#pragma once

#include "TaskBase.h"

namespace Ts
{
	class ConditionalTaskImp;	

	class ConditionalTask : public TaskBase								
	{													
	public:												
		typedef boost::shared_ptr<ConditionalTask>		pointer;		
		typedef boost::shared_ptr<ConditionalTaskImp>	imp_pointer;

	public:			
		virtual ~ConditionalTask();
		static pointer		Create(const WString& taskName, const WString& conditionName, const WString& decoratedTaskName);

	public:

	protected:											
		ConditionalTask();											
	};

}
