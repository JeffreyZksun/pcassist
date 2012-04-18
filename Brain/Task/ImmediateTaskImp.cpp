
#include "stdafx.h"
#include "ImmediateTask.h"
#include "ImmediateTaskImp.h"
#include "ITaskSystem.h"
#include "BehaviorManager.h"
#include "Logger.h" //LogOut
#include <atltime.h> // CTime
#include "ConstantsDefinition.h"

using namespace Ts;

ImmediateTaskImp::ImmediateTaskImp(owner_pointer pSelf, const WString& taskId)			
	: TaskBaseImp(pSelf, taskId)				
{											
}											

bool ImmediateTaskImp::OnExecute(ITaskSystem* pTaskSystem)
{
	if(NULL == pTaskSystem)
		return false;

	BehaviorManager* pBehaviorManager = pTaskSystem->GetBehaviorManager();
	if(NULL == pBehaviorManager)
		return false;

	if(NULL == pTaskSystem)
	{
		LogOut(_T("Invalid TaskSystem Pointer"));
		return false;
	}

	if(NULL == pTaskSystem->GetVariableManager())
	{
		LogOut(_T("Invalid VariableManager Pointer"));
		return false;
	}

	// Log format.
	//	[==========] Task Begin. (##:##:##)// current time
	//	[----------]
	//	[ACTION    ]
	//	[   SUCCESS]
	//	[----------](## ms)
	//
	//	[----------]
	//	[ACTION    ]
	//	[   SUCCESS]
	//	[----------](## ms)
	//	
	//	[==========] Task Finish.(## ms total)

	CTime taskBeginTime = CTime::GetCurrentTime();

	//int hour = taskBeginTime.GetHour();
	//int minute = taskBeginTime.GetMinute();
	//int second = taskBeginTime.GetSecond();

	int succNum = 0;
	int failNum = 0;
	LogOut(_T("[==========]"), COLOR_GREEN); // 10 chars
	LogOut(_T(" Task Begin."));
	CString strStartTime = _T(" (12:14:34)"); 
	strStartTime.Format(_T(" (%d:%d:%d)"), taskBeginTime.GetHour(), taskBeginTime.GetMinute(), taskBeginTime.GetSecond());
	Ts::StringUtil util;
	LogOut(util.convert_to_wstring(strStartTime));
	LogOut(_T("\n")); 

	bool bRet = true;

	for (ActionList::iterator it = m_ActionList.begin(); it != m_ActionList.end(); ++it)
	{
		LogOut(_T("[----------]\n"), COLOR_GREEN); // 10 chars

		CTime actionBeginTime = CTime::GetCurrentTime();

		ActionPtr pCurrentAction = pBehaviorManager->GetActionById((*it).data());
		DATA_ASSERT(pCurrentAction != NULL);
		if(NULL != pCurrentAction)
		{
			bRet = pCurrentAction->Execute();
		}
		else
		{
			LogOut(_T("Error: The action ["), COLOR_RED); 
			LogOut((*it).data(), COLOR_RED); 
			LogOut(_T("] isn't registered.\n"), COLOR_RED); 
			bRet = false;
		}

		CTimeSpan elapsedTime = CTime::GetCurrentTime() - actionBeginTime;

		if(bRet)
			succNum++;
		else
			failNum++;

		LogOut(_T("[----------]"), COLOR_GREEN); // 10 chars
		CString actionDuration = _T(" (10 s)"); 
		actionDuration.Format(_T(" (%d s)"), elapsedTime.GetTotalSeconds());
		LogOut(util.convert_to_wstring(actionDuration));
		LogOut(_T("\n\n")); 

		// Check the BreakOnFail.
		if(pCurrentAction != NULL && !bRet)
		{
			Parameter para;
			bool bExit = pCurrentAction->GetParameterTable().GetParameter(BREAK_ON_FAIL, para);
			if(bExit)
			{
				if( para.GetEvaluatedValue(pTaskSystem->GetVariableManager()).CompareNoCase(_T("true")) == 0)
				{
					LogOut(_T("ERROR: Break the task due to the failed action ["), COLOR_RED); 
					LogOut((*it), COLOR_RED); 
					LogOut(_T("] \n\n"), COLOR_RED); 
					break;
				}
			}
		}

	}

	bRet = (0 == failNum);

	LogOut(_T("[==========]"), COLOR_GREEN); // 10 chars
	LogOut(_T(" Task Finish.")); 
	// Task duration.

	CString taskDuration = _T(" (3620 s)");
	CTimeSpan elapsedTime = CTime::GetCurrentTime() - taskBeginTime;
	taskDuration.Format(_T(" (%d s)"), elapsedTime.GetTotalSeconds());
	LogOut(util.convert_to_wstring(taskDuration));
	LogOut(_T("\n")); 

	// Total
	LogOut(_T("[ TOTAL    ]")); // 10 chars
	CString strNum;
	strNum.Format(_T(" %d actions\n"), m_ActionList.size());
	LogOut(util.convert_to_wstring(strNum));

	// Success
	LogOut(_T("[ SUCCESS  ]"), COLOR_GREEN); // 10 chars
	strNum.Format(_T(" %d actions\n"), succNum);
	LogOut(util.convert_to_wstring(strNum));

	// Fail
	if(!bRet)
	{
		LogOut(_T("[  FAIL    ]"), COLOR_RED); // 10 chars
		strNum.Format(_T(" %d actions\n"), failNum);
		LogOut(util.convert_to_wstring(strNum));
	}

	return bRet;
}

void ImmediateTaskImp::AppendAction(const WString& actionId)
{
	m_ActionList.push_back(actionId);
}

size_t ImmediateTaskImp::GetActionCount()
{
	return m_ActionList.size();
}