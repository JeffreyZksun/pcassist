#include "StdAfx.h"
#include "TaskManager.h"

TEST(ActionTest, ConditionBlockAction)
{
	Condition procCondition(_T("ProcessRunningCondition"));
	{
		Parameter para1(_T("ObjectId"), _T("IsSvchost_exeRunning")); 
		procCondition.GetParameterTable().AddParameter(para1);

		Parameter para2(_T("ProcessName"), _T("svchost.exe")); 
		procCondition.GetParameterTable().AddParameter(para2);
	}

	
	Action blockAction(_T("ConditionBlockAction"));
	{
		Parameter para1(_T("ConditionId"), _T("IsSvchost_exeRunning")); 
		blockAction.GetParameterTable().AddParameter(para1);

		Parameter para2(_T("ExpectedResult"), _T("true")); 
		blockAction.GetParameterTable().AddParameter(para2);
	}

	bool bRet = blockAction.Execute();
	EXPECT_EQ(true, bRet);

}

