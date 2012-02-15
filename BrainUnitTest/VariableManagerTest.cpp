#include "StdAfx.h"
#include "Parameter.h"
#include "BrainApplication.h"
#include "VariableManager.h"

TEST(VariableManagerTest, BuiltInVariable)
{
	VariableManager* pVM = BrainApplication::GetWorkingBrain()->GetVariableManager();

	Parameter para;
	bool bExist = pVM->GetParameter(_T("*ExeModulePath"), para);
	EXPECT_EQ(true, bExist);

	if(bExist)
	{
		CString actual = para.GetEvaluatedValue(); 
		EXPECT_EQ(false, actual.IsEmpty()); // Verify the path should exist.
	}
}

TEST(VariableManagerTest, BuiltInVariable_1)
{
	ApplicationSwitchHelper helper;

	VariableManager* pVM = BrainApplication::GetWorkingBrain()->GetVariableManager();

	Parameter para;
	bool bExist = pVM->GetParameter(_T("*ExeModulePath"), para);
	EXPECT_EQ(true, bExist);

	if(bExist)
	{
		CString actual = para.GetEvaluatedValue(); 
		EXPECT_EQ(false, actual.IsEmpty()); // Verify the path should exist.
	}
}