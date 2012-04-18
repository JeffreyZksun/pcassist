#pragma once

#include "ParameterTable.h"

class ITaskSystem;

namespace Ts
{
	class TaskBase;	

	class TaskBaseImp											
	{															
	public:														
		typedef boost::shared_ptr<TaskBase>		owner_pointer;		
		typedef boost::weak_ptr<TaskBase>		owner_weak_pointer;	

	public:														
		TaskBaseImp(owner_pointer pSelf, const WString& taskId);							
		virtual ~TaskBaseImp();							

		owner_pointer   Self() const;	

	public:
		virtual bool            IsReady(ITaskSystem* pTaskSystem) const;
		virtual WString			GetObjectId() const;
		virtual bool            Execute(ITaskSystem* pTaskSystem);

	protected:
		virtual bool            OnExecute(ITaskSystem* pTaskSystem) = 0;

	public:
		ParameterTable&			GetParameterTable();
		const ParameterTable&	GetParameterTable() const;

	private:													
		owner_weak_pointer			m_pSelf;

		ParameterTable				m_ParameterTable;

		bool						mbIsExecuting; // Don't persist. Used for reference loop check.
	};

}
