#pragma once

#include "ITask.h"

namespace Ts
{
	class ImmediateTaskImp;	

	class ImmediateTask : public ITask								
	{													
	public:												
		typedef boost::shared_ptr<ImmediateTask>	pointer;		
		typedef boost::shared_ptr<ImmediateTaskImp>	imp_pointer;

	public:			
		virtual ~ImmediateTask();
		static pointer		Create();

	public:
		// override ITask
		virtual bool            IsReady();
		virtual bool            Execute();

	protected:											
		ImmediateTask();											

	private:											
		imp_pointer         m_pImp;
	};

}
