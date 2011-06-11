#include "StdAfx.h"
#include "TaskManager.h"
#include <ConstantsDefinition.h>


TEST(TaskManager, Action)
{

	CString appName(_T("S:\\VEX\\pctext\\PcAssist\\bin\\Release_x86\\PC.exe"));
	Action* pAction = new Action(_T("RunProcessAction"));
	Parameter para(APPLICATION_NAME, appName);
	Parameter para2(APPLICATION_PARAMETER, _T("as  ds -?"));
	pAction->AddParameter(para);
	pAction->AddParameter(para2);
	bool ret = pAction->Execute();
	delete pAction;
}
