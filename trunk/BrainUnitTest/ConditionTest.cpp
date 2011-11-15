#include "StdAfx.h"
#include "TaskManager.h"
#include "BrainUtil.h"

#define THIS_APP_NAME _T("BrainUnitTest.exe")

TEST(ConditionTest, RegisterKeyExistsCondition)
{
	{
		Condition regCondition(_T("RegisterKeyExistsCondition"));
		Parameter para1(_T("RootKey"), _T("HKEY_LOCAL_MACHINE"));
		Parameter para2(_T("SubKey"), _T("Software\\Microsoft"));
		regCondition.GetParameterTable().AddParameter(para1);
		regCondition.GetParameterTable().AddParameter(para2);
		bool bRet = regCondition.IsTrue();
		EXPECT_EQ(true, bRet);
	}
	{
		Condition regCondition(_T("RegisterKeyExistsCondition"));
		Parameter para1(_T("RootKey"), _T("HKEY_LOCAL_MACHINE"));
		Parameter para2(_T("SubKey"), _T("Software\\notexitkey"));
		regCondition.GetParameterTable().AddParameter(para1);
		regCondition.GetParameterTable().AddParameter(para2);
		bool bRet = regCondition.IsTrue();
		EXPECT_EQ(false, bRet);
	}

	{
		Condition regCondition(_T("RegisterKeyExistsCondition"));
		Parameter para1(_T("RootKey"), _T("HKEY_LOCAL_MACHINE"));
		Parameter para2(_T("SubKey"), _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\{FE90E978-A98B-45F6-0163-34EBA616B1F6}"));// \\{FE90E978-A98B-45F6-0163-34EBA616B1F6}
		regCondition.GetParameterTable().AddParameter(para1);
		regCondition.GetParameterTable().AddParameter(para2);
		bool bRet = regCondition.IsTrue();
		//EXPECT_EQ(true, bRet);

		//BrainUtil::LogOutLastError(_T("Registry"));
	}

}

TEST(ConditionTest, ProcessRunningCondition_Name_1)
{
	Condition procCondition(_T("ProcessRunningCondition"));
	Parameter para1(_T("ProcessName"), THIS_APP_NAME); //msiexec.exe setup.exe  svchost.exe
	procCondition.GetParameterTable().AddParameter(para1);
	bool bRet = procCondition.IsTrue();
	EXPECT_EQ(true, bRet);
}

TEST(ConditionTest, ProcessRunningCondition_Name_2)
{
	Condition procCondition(_T("ProcessRunningCondition"));
	Parameter para1(_T("ProcessName"), _T("NotExist.exe")); //Use a process name not exist at all.
	procCondition.GetParameterTable().AddParameter(para1);
	bool bRet = procCondition.IsTrue();
	EXPECT_EQ(false, bRet);
}

// Verify existence
TEST(ConditionTest, ProcessRunningCondition_FullName_1)
{
	Parameter path;
	bool bExist = BrainApplication::GetWorkingBrain()->GetVariableManager()->GetParameter(_T("*ExeModulePath"), path);
	EXPECT_EQ(true, bExist);

	CString strPath = path.GetEvaluatedValue();
	strPath += _T("\\") THIS_APP_NAME;

	Condition procCondition(_T("ProcessRunningCondition"));
	Parameter para1(_T("ProcessName"),strPath);
	procCondition.GetParameterTable().AddParameter(para1);
	bool bRet = procCondition.IsTrue();
	EXPECT_EQ(true, bRet);
}

// Verify forward slash
TEST(ConditionTest, ProcessRunningCondition_FullName_2)
{
	Parameter path;
	bool bExist = BrainApplication::GetWorkingBrain()->GetVariableManager()->GetParameter(_T("*ExeModulePath"), path);
	EXPECT_EQ(true, bExist);

	CString strPath = path.GetEvaluatedValue();
	strPath += _T("/") THIS_APP_NAME;

	Condition procCondition(_T("ProcessRunningCondition"));
	Parameter para1(_T("ProcessName"), strPath); 
	procCondition.GetParameterTable().AddParameter(para1);
	bool bRet = procCondition.IsTrue();
	EXPECT_EQ(true, bRet);
}

TEST(ConditionTest, ProcessRunningCondition_FullName_3)
{
	Parameter path;
	bool bExist = BrainApplication::GetWorkingBrain()->GetVariableManager()->GetParameter(_T("*ExeModulePath"), path);
	EXPECT_EQ(true, bExist);

	CString strPath = path.GetEvaluatedValue();
	strPath += _T("\\NotExistPath\\") THIS_APP_NAME;

	Condition procCondition(_T("ProcessRunningCondition"));
	Parameter para1(_T("ProcessName"), strPath);
	procCondition.GetParameterTable().AddParameter(para1);
	bool bRet = procCondition.IsTrue();
	EXPECT_EQ(false, bRet);
}

TEST(ConditionTest, FolderExistsCondition)
{
	Condition folderCondition(_T("FolderExistsCondition"));
	Parameter para1(_T("FolderName"), _T("C:\\")); 
	folderCondition.GetParameterTable().AddParameter(para1);
	bool bRet = folderCondition.IsTrue();
	EXPECT_EQ(true, bRet);
}
