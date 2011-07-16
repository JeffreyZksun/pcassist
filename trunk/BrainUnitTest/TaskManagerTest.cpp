#include "StdAfx.h"
#include "TaskManager.h"
#include <ConstantsDefinition.h>
#include <BrainApplication.h>


TEST(TaskManager, Action)
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

TEST(TaskManager, GetActionByIndex)
{
	BrainApplication::GetWorkingBrain()->GetTaskManager()->deleteRegisteredConditions();

	CString appName(_T("S:\\VEX\\pctext\\PcAssist\\bin\\Release_x86\\PC.exe"));
	Action* pAction = new Action(_T("RunProcessAction"));
	Parameter para(APPLICATION_NAME, appName);
	Parameter para2(APPLICATION_PARAMETER, _T("as  ds -?"));
	pAction->AddParameter(para);
	pAction->AddParameter(para2);

	Action* pTmpAction = BrainApplication::GetWorkingBrain()->GetTaskManager()->GetActionByIndex(1);
	EXPECT_EQ(true, NULL == pTmpAction);

	pTmpAction = BrainApplication::GetWorkingBrain()->GetTaskManager()->GetActionByIndex(0);
	EXPECT_EQ(false, NULL == pTmpAction);

	if(pTmpAction != NULL)
	{
		Parameter tampPara;
		pTmpAction->GetParameter(APPLICATION_NAME, tampPara);

		bool bmatch = appName.Compare(appName) == 0;
		EXPECT_EQ(true, bmatch);
	}
	delete pAction;
}
