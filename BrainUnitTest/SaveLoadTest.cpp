#include "StdAfx.h"

#include "BrainApplication.h"
#include "Parameter.h"
#include "TaskManager.h"
#include "VariableManager.h"
#include "ConstantsDefinition.h"

TEST(SaveLoadTest, SaveLoadLatestVersion)
{
	// Use the temp application.
	BrainApplication *pTempApp1 = new BrainApplication();
	BrainApplication* pPreviousApp = BrainApplication::SetWorkingBrain(pTempApp1);

	{
		Parameter para(_T("OS"), _T("Windows7"));
		para.SetComments(_T("global"));
		BrainApplication::GetWorkingBrain()->GetVariableManager()->GetParameterTable().AddParameter(para);
	}

	CString conditionId = _T("DoesRegExist");
	{
		Condition *pRegCondition = new Condition(_T("RegisterKeyExistsCondition"));
		Parameter objectId(OBJECT_ID, conditionId);
		Parameter para1(_T("RootKey"), _T("HKEY_LOCAL_MACHINE"));
		Parameter para2(_T("SubKey"), _T("Software\\Microsoft"));

		pRegCondition->GetParameterTable().AddParameter(objectId);
		pRegCondition->GetParameterTable().AddParameter(para1);
		pRegCondition->GetParameterTable().AddParameter(para2);

		//BrainApplication::GetWorkingBrain()->GetTaskManager()->RegisterCondition(pRegCondition);
	}

	CString actionId = _T("DemoToRunSysCmd");
	{
		Action *pNewAction = new Action(_T("RunSystemCommandAction"));
		Parameter objectId(OBJECT_ID, actionId);
		objectId.SetComments(_T("Object Id is used to reference this object everywhere."));
		Parameter objectType;
		pNewAction->GetParameterTable().GetParameter(OBJECT_TYPE, objectType);
		objectType.SetComments(_T("Object type indicates which behavior body will this action invokes."));
		Parameter cmd(APPLICATION_NAME, _T("regedit.exe"));
		cmd.SetComments(_T("Indicate which command will be run"));
		pNewAction->GetParameterTable().AddParameter(objectId);
		pNewAction->GetParameterTable().AddParameter(objectType);
		pNewAction->GetParameterTable().AddParameter(cmd);

		//BrainApplication::GetWorkingBrain()->GetTaskManager()->RegisterAction(pNewAction);
		BrainApplication::GetWorkingBrain()->GetTaskManager()->AddActionTask(pNewAction);
	}

	CString fileName(_T("C:\\braintest.xml"));

	// Save
	bool ret = BrainApplication::GetWorkingBrain()->XmlOut(fileName);
	EXPECT_EQ(true, ret);

	// Load
	BrainApplication *pTempApp2 = new BrainApplication();

	BrainApplication::SetWorkingBrain(pTempApp2);

	ret = BrainApplication::GetWorkingBrain()->XmlIn(fileName);
	EXPECT_EQ(true, ret);

	{
		Action* pAction = BrainApplication::GetWorkingBrain()->GetTaskManager()->GetActionById(actionId);
		EXPECT_EQ(true, (pAction != NULL));
	}

	{
		Condition* pCondition = BrainApplication::GetWorkingBrain()->GetTaskManager()->GetConditionById(conditionId);
		EXPECT_EQ(true, (pCondition != NULL));
	}

	// Recover
	BrainApplication::SetWorkingBrain(pPreviousApp);
}

TEST(SaveLoadTest, LoadDocVersion1)
{
	

	// Use the temp application.
	BrainApplication *pTempApp1 = new BrainApplication();
	BrainApplication* pPreviousApp = BrainApplication::SetWorkingBrain(pTempApp1);

	CString fileName(_T("DocVersion1.xml"));
	bool ret = BrainApplication::GetWorkingBrain()->XmlIn(fileName);
	EXPECT_EQ(true, ret);

	{
		CString actionId = _T("DemoToRunSysCmd");
		Action* pAction = BrainApplication::GetWorkingBrain()->GetTaskManager()->GetActionById(actionId);
		EXPECT_EQ(true, (pAction != NULL));
	}

	{
		CString conditionId = _T("DoesRegExist");
		Condition* pCondition = BrainApplication::GetWorkingBrain()->GetTaskManager()->GetConditionById(conditionId);
		EXPECT_EQ(true, (pCondition != NULL));
	}

	// ToDo - we need to check more items here.

	// Recover
	BrainApplication::SetWorkingBrain(pPreviousApp);
}

TEST(SaveLoadTest, SaveLoadDocVersion1)
{
	CString content = _T("");

	// Use the temp application.
	BrainApplication *pTempApp1 = new BrainApplication();
	BrainApplication* pPreviousApp = BrainApplication::SetWorkingBrain(pTempApp1);

	// Recover
	BrainApplication::SetWorkingBrain(pPreviousApp);
}