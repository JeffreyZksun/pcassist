#include "StdAfx.h"
#include "TaskManager.h"
#include "BrainUtil.h"

#define THIS_APP_NAME _T("BrainUnitTest.exe")

TEST(ConditionTest, RegisterKeyExistsCondition)
{
    ApplicationSwitchHelper helper;

	{
		Condition regCondition(GetWorkingBrain()->GetTaskManager(), _T("RegisterKeyExistsCondition"));
		Parameter para1(_T("RootKey"), _T("HKEY_LOCAL_MACHINE"));
		Parameter para2(_T("SubKey"), _T("Software\\Microsoft"));
		regCondition.GetParameterTable().AddParameter(para1);
		regCondition.GetParameterTable().AddParameter(para2);
		bool bRet = regCondition.IsTrue();
		EXPECT_EQ(true, bRet);
	}
	{
		Condition regCondition(GetWorkingBrain()->GetTaskManager(), _T("RegisterKeyExistsCondition"));
		Parameter para1(_T("RootKey"), _T("HKEY_LOCAL_MACHINE"));
		Parameter para2(_T("SubKey"), _T("Software\\notexitkey"));
		regCondition.GetParameterTable().AddParameter(para1);
		regCondition.GetParameterTable().AddParameter(para2);
		bool bRet = regCondition.IsTrue();
		EXPECT_EQ(false, bRet);
	}

	{
		Condition regCondition(GetWorkingBrain()->GetTaskManager(), _T("RegisterKeyExistsCondition"));
		Parameter para1(_T("RootKey"), _T("HKEY_LOCAL_MACHINE"));
		Parameter para2(_T("SubKey"), _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\{FE90E978-A98B-45F6-0163-34EBA616B1F6}"));// \\{FE90E978-A98B-45F6-0163-34EBA616B1F6}
		regCondition.GetParameterTable().AddParameter(para1);
		regCondition.GetParameterTable().AddParameter(para2);
		bool bRet = regCondition.IsTrue();
		//EXPECT_EQ(true, bRet); // This key is for real dwg jaws. The condition is false if RealDWG isn't installed.

		//BrainUtil::LogOutLastError(_T("Registry"));
	}

}

TEST(ConditionTest, ProcessRunningCondition_Name_1)
{
    ApplicationSwitchHelper helper;

	Condition procCondition(GetWorkingBrain()->GetTaskManager(), _T("ProcessRunningCondition"));
	Parameter para1(_T("ProcessName"), THIS_APP_NAME); //msiexec.exe setup.exe  svchost.exe
	procCondition.GetParameterTable().AddParameter(para1);
	bool bRet = procCondition.IsTrue();
	EXPECT_EQ(true, bRet);
}

TEST(ConditionTest, ProcessRunningCondition_Name_2)
{
	Condition procCondition(GetWorkingBrain()->GetTaskManager(), _T("ProcessRunningCondition"));
	Parameter para1(_T("ProcessName"), _T("NotExist.exe")); //Use a process name not exist at all.
	procCondition.GetParameterTable().AddParameter(para1);
	bool bRet = procCondition.IsTrue();
	EXPECT_EQ(false, bRet);
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

	Condition procCondition(GetWorkingBrain()->GetTaskManager(), _T("ProcessRunningCondition"));
	Parameter para1(_T("ProcessName"),strPath);
	procCondition.GetParameterTable().AddParameter(para1);
	bool bRet = procCondition.IsTrue();
	EXPECT_EQ(true, bRet);
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

	Condition procCondition(GetWorkingBrain()->GetTaskManager(), _T("ProcessRunningCondition"));
	Parameter para1(_T("ProcessName"), strPath); 
	procCondition.GetParameterTable().AddParameter(para1);
	bool bRet = procCondition.IsTrue();
	EXPECT_EQ(true, bRet);
}

TEST(ConditionTest, ProcessRunningCondition_FullName_3)
{
    ApplicationSwitchHelper helper;

	Parameter path;
	bool bExist = GetWorkingBrain()->GetVariableManager()->GetParameter(_T("*ExeModulePath"), path);
	EXPECT_EQ(true, bExist);

	CString strPath = path.GetEvaluatedValue(GetWorkingBrain()->GetVariableManager());
	strPath += _T("\\NotExistPath\\") THIS_APP_NAME;

	Condition procCondition(GetWorkingBrain()->GetTaskManager(), _T("ProcessRunningCondition"));
	Parameter para1(_T("ProcessName"), strPath);
	procCondition.GetParameterTable().AddParameter(para1);
	bool bRet = procCondition.IsTrue();
	EXPECT_EQ(false, bRet);
}

TEST(ConditionTest, FolderExistsCondition)
{
    ApplicationSwitchHelper helper;

	Condition folderCondition(GetWorkingBrain()->GetTaskManager(), _T("FolderExistsCondition"));
	Parameter para1(_T("FolderName"), _T("C:\\")); 
	folderCondition.GetParameterTable().AddParameter(para1);
	bool bRet = folderCondition.IsTrue();
	EXPECT_EQ(true, bRet);
}

TEST(ConditionTest, ActionResultCondition)
{
    ApplicationSwitchHelper helper;

    {
        Action* pAction = new Action(GetWorkingBrain()->GetTaskManager(), _T("RunProcessAction"));
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

    Condition checker(GetWorkingBrain()->GetTaskManager(), _T("ActionResultCondition"));
    {
        
        Parameter para1(_T("ActionId"), _T("StartNotepad")); 
        checker.GetParameterTable().AddParameter(para1);
    }

    bool bRet = checker.IsTrue();

    EXPECT_EQ(true, bRet);
}
