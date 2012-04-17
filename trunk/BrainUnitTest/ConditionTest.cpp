#include "StdAfx.h"
#include "BehaviorManager.h"
#include "BrainUtil.h"

#define THIS_APP_NAME _T("BrainUnitTest.exe")

TEST(ConditionTest, RegisterKeyExistsCondition)
{
    ApplicationSwitchHelper helper;

	{
		ConditionPtr pRegCondition = Condition::Create(_T("RegisterKeyExistsCondition"), GetWorkingBrain()->GetBehaviorManager());
		//Condition regCondition(GetWorkingBrain()->GetBehaviorManager(), _T("RegisterKeyExistsCondition"));
		Parameter para1(_T("RootKey"), _T("HKEY_LOCAL_MACHINE"));
		Parameter para2(_T("SubKey"), _T("Software\\Microsoft"));
		pRegCondition->GetParameterTable().AddParameter(para1);
		pRegCondition->GetParameterTable().AddParameter(para2);
		bool bRet = pRegCondition->IsTrue();
		EXPECT_EQ(true, bRet);

		GetWorkingBrain()->GetBehaviorManager()->UnregisterCondition(pRegCondition);
	}
	{
		ConditionPtr pRegCondition = Condition::Create(_T("RegisterKeyExistsCondition"), GetWorkingBrain()->GetBehaviorManager());
		Parameter para1(_T("RootKey"), _T("HKEY_LOCAL_MACHINE"));
		Parameter para2(_T("SubKey"), _T("Software\\notexitkey"));
		pRegCondition->GetParameterTable().AddParameter(para1);
		pRegCondition->GetParameterTable().AddParameter(para2);
		bool bRet = pRegCondition->IsTrue();
		EXPECT_EQ(false, bRet);
		GetWorkingBrain()->GetBehaviorManager()->UnregisterCondition(pRegCondition);

	}

	{
		ConditionPtr pRegCondition = Condition::Create(_T("RegisterKeyExistsCondition"), GetWorkingBrain()->GetBehaviorManager());
		Parameter para1(_T("RootKey"), _T("HKEY_LOCAL_MACHINE"));
		Parameter para2(_T("SubKey"), _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\{FE90E978-A98B-45F6-0163-34EBA616B1F6}"));// \\{FE90E978-A98B-45F6-0163-34EBA616B1F6}
		pRegCondition->GetParameterTable().AddParameter(para1);
		pRegCondition->GetParameterTable().AddParameter(para2);
		bool bRet = pRegCondition->IsTrue();
		//EXPECT_EQ(true, bRet); // This key is for real dwg jaws. The condition is false if RealDWG isn't installed.

		//BrainUtil::LogOutLastError(_T("Registry"));
		GetWorkingBrain()->GetBehaviorManager()->UnregisterCondition(pRegCondition);

	}

}

TEST(ConditionTest, ProcessRunningCondition_Name_1)
{
    ApplicationSwitchHelper helper;

	ConditionPtr pProcCondition = Condition::Create(_T("ProcessRunningCondition"), GetWorkingBrain()->GetBehaviorManager());
	Parameter para1(_T("ProcessName"), THIS_APP_NAME); //msiexec.exe setup.exe  svchost.exe
	pProcCondition->GetParameterTable().AddParameter(para1);
	bool bRet = pProcCondition->IsTrue();
	EXPECT_EQ(true, bRet);

	GetWorkingBrain()->GetBehaviorManager()->UnregisterCondition(pProcCondition);

}

TEST(ConditionTest, ProcessRunningCondition_Name_2)
{
	ConditionPtr pProcCondition = Condition::Create(_T("ProcessRunningCondition"), GetWorkingBrain()->GetBehaviorManager());

	Parameter para1(_T("ProcessName"), _T("NotExist.exe")); //Use a process name not exist at all.
	pProcCondition->GetParameterTable().AddParameter(para1);
	bool bRet = pProcCondition->IsTrue();
	EXPECT_EQ(false, bRet);

	GetWorkingBrain()->GetBehaviorManager()->UnregisterCondition(pProcCondition);

}

// Verify existence
TEST(ConditionTest, ProcessRunningCondition_FullName_1)
{
    ApplicationSwitchHelper helper;

	Parameter path;
	bool bExist = GetWorkingBrain()->GetVariableManager()->GetParameter(_T("*ExeModulePath"), path);
	EXPECT_EQ(true, bExist);

	CString strPath = path.GetEvaluatedValue(GetWorkingBrain()->GetVariableManager());
	strPath += _T("\\") THIS_APP_NAME;

	ConditionPtr pProcCondition = Condition::Create(_T("ProcessRunningCondition"), GetWorkingBrain()->GetBehaviorManager());

	Parameter para1(_T("ProcessName"),strPath);
	pProcCondition->GetParameterTable().AddParameter(para1);
	bool bRet = pProcCondition->IsTrue();
	EXPECT_EQ(true, bRet);

	GetWorkingBrain()->GetBehaviorManager()->UnregisterCondition(pProcCondition);
}

// Verify forward slash
TEST(ConditionTest, ProcessRunningCondition_FullName_2)
{
    ApplicationSwitchHelper helper;

	Parameter path;
	bool bExist = GetWorkingBrain()->GetVariableManager()->GetParameter(_T("*ExeModulePath"), path);
	EXPECT_EQ(true, bExist);

	CString strPath = path.GetEvaluatedValue(GetWorkingBrain()->GetVariableManager());
	strPath += _T("/") THIS_APP_NAME;

	ConditionPtr pProcCondition = Condition::Create(_T("ProcessRunningCondition"), GetWorkingBrain()->GetBehaviorManager());

	Parameter para1(_T("ProcessName"), strPath); 
	pProcCondition->GetParameterTable().AddParameter(para1);
	bool bRet = pProcCondition->IsTrue();
	EXPECT_EQ(true, bRet);

	GetWorkingBrain()->GetBehaviorManager()->UnregisterCondition(pProcCondition);

}

TEST(ConditionTest, ProcessRunningCondition_FullName_3)
{
    ApplicationSwitchHelper helper;

	Parameter path;
	bool bExist = GetWorkingBrain()->GetVariableManager()->GetParameter(_T("*ExeModulePath"), path);
	EXPECT_EQ(true, bExist);

	CString strPath = path.GetEvaluatedValue(GetWorkingBrain()->GetVariableManager());
	strPath += _T("\\NotExistPath\\") THIS_APP_NAME;

	ConditionPtr pProcCondition = Condition::Create(_T("ProcessRunningCondition"), GetWorkingBrain()->GetBehaviorManager());

	Parameter para1(_T("ProcessName"), strPath);
	pProcCondition->GetParameterTable().AddParameter(para1);
	bool bRet = pProcCondition->IsTrue();
	EXPECT_EQ(false, bRet);

	GetWorkingBrain()->GetBehaviorManager()->UnregisterCondition(pProcCondition);

}

TEST(ConditionTest, FolderExistsCondition)
{
    ApplicationSwitchHelper helper;

	ConditionPtr pFolderCondition = Condition::Create(_T("FolderExistsCondition"), GetWorkingBrain()->GetBehaviorManager());
	Parameter para1(_T("FolderName"), _T("C:\\")); 
	pFolderCondition->GetParameterTable().AddParameter(para1);
	bool bRet = pFolderCondition->IsTrue();
	EXPECT_EQ(true, bRet);

	GetWorkingBrain()->GetBehaviorManager()->UnregisterCondition(pFolderCondition);

}

TEST(ConditionTest, ActionResultCondition)
{
    ApplicationSwitchHelper helper;

    {
        ActionPtr pAction = Action::Create(_T("RunProcessAction"), GetWorkingBrain()->GetBehaviorManager());
        Parameter para0(_T("ObjectId"), _T("StartNotepad")); 
        Parameter para1(_T("ApplicationName"), _T("C:\\Windows\\System32\\notepad.exe")); 
        Parameter para2(_T("ApplicationParameter"), _T("")); 
        Parameter para3(_T("ShowWindow"), _T("true")); 
        Parameter para4(_T("WaitForExit"), _T("false")); 

        pAction->GetParameterTable().AddParameter(para0);
        pAction->GetParameterTable().AddParameter(para1);
        pAction->GetParameterTable().AddParameter(para2);
        pAction->GetParameterTable().AddParameter(para3);
        pAction->GetParameterTable().AddParameter(para4);
    }

    ConditionPtr pChecker = Condition::Create(_T("ActionResultCondition"), GetWorkingBrain()->GetBehaviorManager());
    {
        
        Parameter para1(_T("ActionId"), _T("StartNotepad")); 
        pChecker->GetParameterTable().AddParameter(para1);
    }

    bool bRet = pChecker->IsTrue();

    EXPECT_EQ(true, bRet);

	GetWorkingBrain()->GetBehaviorManager()->UnregisterCondition(pChecker);

}
