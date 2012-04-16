#pragma once

#include "ITask.h"

namespace Ts
{
	class TaskBaseImp;	

	class TaskBase : public ITask								
	{													
	public:												
		typedef boost::shared_ptr<TaskBase>	pointer;		
		typedef boost::shared_ptr<TaskBaseImp>	imp_pointer;

	public:			
		virtual ~TaskBase();

	public:
		// override ITask
		virtual bool            IsReady(ITaskSystem* pTaskSystem) const;
		virtual	const WString&	GetName() const;
		virtual bool            Execute(ITaskSystem* pTaskSystem);

	protected:
		imp_pointer				GetImp() const;
		void					SetImp(imp_pointer pImp);

	protected:											
		TaskBase();											

	private:											
		imp_pointer         m_pImp;
	};

}
