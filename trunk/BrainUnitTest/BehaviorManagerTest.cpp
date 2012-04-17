#include "StdAfx.h"
#include "BehaviorManager.h"
#include <ConstantsDefinition.h>
#include <TaskSystem.h>


TEST(BehaviorManager, Action)
{

	//CString appName(_T("S:\\VEX\\pctext\\PcAssist\\bin\\Release_x86\\PC.exe"));
	//Action* pAction = new Action(_T("RunProcessAction"));
	//Parameter para(APPLICATION_NAME, appName);
	//Parameter para2(APPLICATION_PARAMETER, _T("as  ds -?"));
	//pAction->AddParameter(para);
	//pAction->AddParameter(para2);
	//bool ret = pAction->Execute();
	//delete pAction;
}

TEST(BehaviorManager, GetActionByIndex)
{
	GetWorkingBrain()->GetBehaviorManager()->deleteRegisteredConditions();

	CString appName(_T("S:\\VEX\\pctext\\PcAssist\\bin\\Release_x86\\PC.exe"));
	Action* pAction = new Action(GetWorkingBrain()->GetBehaviorManager(), _T("RunProcessAction"));
	Parameter para(APPLICATION_NAME, appName);
	Parameter para2(APPLICATION_PARAMETER, _T("as  ds -?"));
	pAction->GetParameterTable().AddParameter(para);
	pAction->GetParameterTable().AddParameter(para2);

	Action* pTmpAction = GetWorkingBrain()->GetBehaviorManager()->GetActionByIndex(1);
	EXPECT_EQ(true, NULL == pTmpAction);

	pTmpAction = GetWorkingBrain()->GetBehaviorManager()->GetActionByIndex(0);
	EXPECT_EQ(false, NULL == pTmpAction);

	if(pTmpAction != NULL)
	{
		Parameter tampPara;
		pTmpAction->GetParameterTable().GetParameter(APPLICATION_NAME, tampPara);

		bool bmatch = appName.Compare(appName) == 0;
		EXPECT_EQ(true, bmatch);
	}
	delete pAction;
}
