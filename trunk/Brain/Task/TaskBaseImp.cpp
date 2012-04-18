
#include "stdafx.h"

#include "TaskBaseImp.h"

using namespace Ts;

TaskBaseImp::TaskBaseImp(owner_pointer pSelf, const WString& taskId)			
	: m_pSelf(pSelf), m_ParameterTable()						
{
	m_ParameterTable.AddParameter(Parameter(OBJECT_ID, taskId.data()));	// Used for query the object
}

TaskBaseImp::~TaskBaseImp()
{

}

TaskBaseImp::owner_pointer TaskBaseImp::Self() const	
{											
	return m_pSelf.lock();					
}

bool TaskBaseImp::IsReady(ITaskSystem* pTaskSystem) const
{
	if(NULL == pTaskSystem)
		return false;

	return true;
}

WString	TaskBaseImp::GetObjectId() const
{
	const Parameter* pPara = m_ParameterTable.GetParameter(OBJECT_ID);
	DATA_ASSERT(pPara);
	if(!pPara)
		return _T("");

	return (WString(pPara->GetRawValue()));
}

ParameterTable&	TaskBaseImp::GetParameterTable()
{
	return m_ParameterTable;
}

const ParameterTable& TaskBaseImp::GetParameterTable() const
{
	return m_ParameterTable;
}

bool TaskBaseImp::Execute(ITaskSystem* pTaskSystem)
{
	if(true == mbIsExecuting)
	{
		DATA_ASSERT(!_T("Error: Task execution loop is detected"));
		LogOut(_T("Error: Task execution loop is detected=> "), COLOR_RED);
		LogOut(GetObjectId().data(), COLOR_RED);
		LogOut(_T("\n"), COLOR_RED);
		return false;
	}

	mbIsExecuting = true;

	bool bSucc = OnExecute(pTaskSystem);

	mbIsExecuting = false;

	return bSucc;

}
