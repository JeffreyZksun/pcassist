#include "StdAfx.h"
#include "TaskManager.h"
#include "BrainUtil.h"

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

TEST(ConditionTest, ProcessRunningCondition)
{
	Condition procCondition(_T("ProcessRunningCondition"));
	Parameter para1(_T("ProcessName"), _T("svchost.exe")); //msiexec.exe setup.exe  svchost.exe
	procCondition.GetParameterTable().AddParameter(para1);
	bool bRet = procCondition.IsTrue();
	EXPECT_EQ(true, bRet);
}
