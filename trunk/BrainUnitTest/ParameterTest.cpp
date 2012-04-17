#include "StdAfx.h"
#include "Parameter.h"
#include "TaskSystem.h"
#include "VariableManager.h"

TEST(ParameterTest, EvaluationLoop)
{
	ApplicationSwitchHelper helper;

	VariableManager* pVM = GetWorkingBrain()->GetVariableManager();
	{
		Parameter para1(_T("A"), _T("A%B%A"));
		pVM->AddUserParameter(para1);
	}

	{
		Parameter para2(_T("B"), _T("B%C%B"));
		pVM->AddUserParameter(para2);
	}

	Parameter para3(_T("C"), _T("C%A%C"));
	pVM->AddUserParameter(para3);

	Ts::DisableAssert(); // The assert is expected due to the loop
	CString actual = para3.GetEvaluatedValue(GetWorkingBrain()->GetVariableManager());
	Ts::EnableAssert();
	CString expected = _T("CABBAC");

	bool bmatch = actual.Compare(expected) == 0;
	EXPECT_EQ(true, bmatch);
}

TEST(ParameterTest, Evaluation)
{
	ApplicationSwitchHelper helper;

	VariableManager* pVM = GetWorkingBrain()->GetVariableManager();
	{
		Parameter para1(_T("ParameterTest_A"), _T("A%ParameterTest_B%A"));
		pVM->AddUserParameter(para1);
	}

	{
		Parameter para2(_T("ParameterTest_B"), _T("ParameterTest_B_Value"));
		pVM->AddUserParameter(para2);
	}

	Parameter para3(_T("ParameterTest_C"), _T("C%ParameterTest_A%C"));
	pVM->AddUserParameter(para3);

	CString actual = para3.GetEvaluatedValue(GetWorkingBrain()->GetVariableManager()); 
	CString expected = _T("CAParameterTest_B_ValueAC");

	bool bmatch = actual.Compare(expected) == 0;
	EXPECT_EQ(true, bmatch);
}
