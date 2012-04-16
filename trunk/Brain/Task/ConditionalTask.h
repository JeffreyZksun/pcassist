#pragma once

#include "ITask.h"

namespace Ts
{
	class ConditionalTaskImp;	

	class ConditionalTask : public ITask								
	{													
	public:												
		typedef boost::shared_ptr<ConditionalTask>		pointer;		
		typedef boost::shared_ptr<ConditionalTaskImp>	imp_pointer;

	public:			
		virtual ~ConditionalTask();
		static pointer		Create();

	public:
		// override ITask
		virtual bool            IsReady();
		virtual bool            Execute();

	protected:											
		ConditionalTask();											

	private:											
		imp_pointer         m_pImp;
	};

}
