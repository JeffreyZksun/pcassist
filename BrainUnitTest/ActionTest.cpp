#include "StdAfx.h"
#include "BehaviorManager.h"

#define THIS_APP_NAME _T("BrainUnitTest.exe")

TEST(ActionTest, ConditionBlockAction)
{
	ConditionPtr pCondition = Condition::Create( _T("ProcessRunningCondition"), GetWorkingBrain()->GetBehaviorManager());
	//Condition procCondition(GetWorkingBrain()->GetBehaviorManager(), _T("ProcessRunningCondition"));
	{
		Parameter para1(_T("ObjectId"), _T("IsUnitTest_exeRunning")); 
		pCondition->GetParameterTable().AddParameter(para1);

		Parameter para2(_T("ProcessName"), THIS_APP_NAME); 
		pCondition->GetParameterTable().AddParameter(para2);
	}

	ActionPtr pBlockAction = Action::Create(_T("ConditionBlockAction"), GetWorkingBrain()->GetBehaviorManager());
	//Action blockAction(GetWorkingBrain()->GetBehaviorManager(), _T("ConditionBlockAction"));
	{
		Parameter para1(_T("ConditionId"), _T("IsUnitTest_exeRunning")); 
		pBlockAction->GetParameterTable().AddParameter(para1);

		Parameter para2(_T("ExpectedResult"), _T("true")); 
		pBlockAction->GetParameterTable().AddParameter(para2);
	}

	bool bRet = pBlockAction->Execute();
	EXPECT_EQ(true, bRet);

	GetWorkingBrain()->GetBehaviorManager()->UnregisterAction(pBlockAction);
}

// 
// A1: if(C) {Execute A2}
// A2: if(C) {Execute A1}
// Execute A2. Verify the loop below can be detected
TEST(ActionTest, ReferenceLoopAction)
{
	ApplicationSwitchHelper helper;

	{
		ConditionPtr pC = Condition::Create(_T("FolderExistsCondition"), GetWorkingBrain()->GetBehaviorManager());
		//Condition *pC = Condition::Create(GetWorkingBrain()->GetBehaviorManager(), _T("FolderExistsCondition"));
		Parameter para1(_T("ObjectId"), _T("C")); 
		Parameter para2(_T("FolderName"), _T("C:\\")); 
		pC->GetParameterTable().AddParameter(para1);
		pC->GetParameterTable().AddParameter(para2);
	}

	{
		ActionPtr pA1 = Action::Create(_T("ComplexAction"), GetWorkingBrain()->GetBehaviorManager());
		Parameter para1(_T("ObjectId"), _T("A1")); 
		Parameter para2(_T("MainAction"), _T("A2"));
		Parameter para3(_T("ExecuteCondition"), _T("C"));
		pA1->GetParameterTable().AddParameter(para1);
		pA1->GetParameterTable().AddParameter(para2);
		pA1->GetParameterTable().AddParameter(para3);

	}

	ActionPtr pA2 = Action::Create(_T("ComplexAction"), GetWorkingBrain()->GetBehaviorManager());
	{
		Parameter para1(_T("ObjectId"), _T("A2")); 
		Parameter para2(_T("MainAction"), _T("A1"));
		Parameter para3(_T("ExecuteCondition"), _T("C"));
		pA2->GetParameterTable().AddParameter(para1);
		pA2->GetParameterTable().AddParameter(para2);
		pA2->GetParameterTable().AddParameter(para3);
	}

	bool bRet = pA2->Execute(); // The assert is expected.
	EXPECT_EQ(false, bRet);

	GetWorkingBrain()->GetBehaviorManager()->UnregisterAction(pA2);

}


TEST(ActionTest, RunProcessAction)
{

	ActionPtr pProcessAction = Action::Create(_T("RunProcessAction"), GetWorkingBrain()->GetBehaviorManager());
	{
		Parameter para1(_T("ApplicationName"), _T("C:\\Windows\\System32\\notepad.exe")); 
		Parameter para2(_T("ApplicationParameter"), _T("")); 
		Parameter para3(_T("ShowWindow"), _T("true")); 
		Parameter para4(_T("WaitForExit"), _T("false")); 

		pProcessAction->GetParameterTable().AddParameter(para1);
		pProcessAction->GetParameterTable().AddParameter(para2);
		pProcessAction->GetParameterTable().AddParameter(para3);
		pProcessAction->GetParameterTable().AddParameter(para4);
	}

	bool bRet = pProcessAction->Execute();
	EXPECT_EQ(true, bRet);

	GetWorkingBrain()->GetBehaviorManager()->UnregisterAction(pProcessAction);

}

TEST(ActionTest, TaskListAction)
{
    ApplicationSwitchHelper helper;

    {
        ActionPtr pAction = Action::Create(_T("RunSystemCommandAction"), GetWorkingBrain()->GetBehaviorManager());
        Parameter para0(_T("ObjectId"), _T("EchoMessage")); 
        Parameter para1(_T("ApplicationName"), _T("echo Hello world")); 
        Parameter para2(_T("ApplicationParameter"), _T("")); 


        pAction->GetParameterTable().AddParameter(para0);
        pAction->GetParameterTable().AddParameter(para1);
        pAction->GetParameterTable().AddParameter(para2);
    }

    ActionPtr pTaskList = Action::Create(_T("TaskListAction"), GetWorkingBrain()->GetBehaviorManager());
    {

        Parameter para1(_T("IdList"), _T("{EchoMessage}")); 
        pTaskList->GetParameterTable().AddParameter(para1);
    }

    bool bRet = pTaskList->Execute();

    EXPECT_EQ(true, bRet);

	GetWorkingBrain()->GetBehaviorManager()->UnregisterAction(pTaskList);

}

TEST(ActionTest, TaskListAction_2)
{
    ApplicationSwitchHelper helper;

    {
        ActionPtr pAction = Action::Create( _T("RunSystemCommandAction"), GetWorkingBrain()->GetBehaviorManager());
        Parameter para0(_T("ObjectId"), _T("EchoMessage")); 
        Parameter para1(_T("ApplicationName"), _T("echo Hello world")); 
        Parameter para2(_T("ApplicationParameter"), _T("")); 


        pAction->GetParameterTable().AddParameter(para0);
        pAction->GetParameterTable().AddParameter(para1);
        pAction->GetParameterTable().AddParameter(para2);
    }

    ActionPtr pTaskList = Action::Create(_T("TaskListAction"), GetWorkingBrain()->GetBehaviorManager());
    {

        Parameter para1(_T("IdList"), _T("{EchoMessage}{DummyAction}")); 
        pTaskList->GetParameterTable().AddParameter(para1);
    }

    bool bRet = pTaskList->Execute();

    EXPECT_EQ(false, bRet);

	GetWorkingBrain()->GetBehaviorManager()->UnregisterAction(pTaskList);
}

TEST(ActionTest, ConditionListCheckAction_1)
{
    ApplicationSwitchHelper helper;

    {
        ConditionPtr pFolderCondition = Condition::Create(_T("FolderExistsCondition"), GetWorkingBrain()->GetBehaviorManager());
        Parameter para1(_T("ObjectId"), _T("VerifyFolderCExist")); 
        Parameter para2(_T("FolderName"), _T("C:\\")); 

        pFolderCondition->GetParameterTable().AddParameter(para1);
        pFolderCondition->GetParameterTable().AddParameter(para2);
    }

    ActionPtr pSanityCheck = Action::Create(_T("ConditionListCheckAction"), GetWorkingBrain()->GetBehaviorManager());
    {

        Parameter para1(_T("IdList"), _T("{VerifyFolderCExist}")); 
        pSanityCheck->GetParameterTable().AddParameter(para1);
    }

    bool bRet = pSanityCheck->Execute();
    EXPECT_EQ(true, bRet);

	GetWorkingBrain()->GetBehaviorManager()->UnregisterAction(pSanityCheck);
}

TEST(ActionTest, ConditionListCheckAction_2)
{
    ApplicationSwitchHelper helper;

    {
        ConditionPtr pFolderCondition = Condition::Create(_T("FolderExistsCondition"), GetWorkingBrain()->GetBehaviorManager());
        Parameter para1(_T("ObjectId"), _T("VerifyFolderCExist")); 
        Parameter para2(_T("FolderName"), _T("C:\\")); 

        pFolderCondition->GetParameterTable().AddParameter(para1);
        pFolderCondition->GetParameterTable().AddParameter(para2);
    }

    {
        ConditionPtr pFolderCondition = Condition::Create(_T("FolderExistsCondition"), GetWorkingBrain()->GetBehaviorManager());
        Parameter para1(_T("ObjectId"), _T("VerifyFolderZZExist")); 
        Parameter para2(_T("FolderName"), _T("ZZ:\\")); 

        pFolderCondition->GetParameterTable().AddParameter(para1);
        pFolderCondition->GetParameterTable().AddParameter(para2);
    }

    ActionPtr pSanityCheck = Action::Create(_T("ConditionListCheckAction"), GetWorkingBrain()->GetBehaviorManager());
    {

        Parameter para1(_T("IdList"), _T("{VerifyFolderCExist} {VerifyFolderZZExist}")); 
        pSanityCheck->GetParameterTable().AddParameter(para1);
    }

    bool bRet = pSanityCheck->Execute();
    EXPECT_EQ(false, bRet);

	GetWorkingBrain()->GetBehaviorManager()->UnregisterAction(pSanityCheck);
}


TEST(ActionTest, ConditionListCheckAction_3)
{
    ApplicationSwitchHelper helper;

    {
        ConditionPtr pFolderCondition = Condition::Create(_T("FolderExistsCondition"), GetWorkingBrain()->GetBehaviorManager());
        Parameter para1(_T("ObjectId"), _T("VerifyFolderCExist")); 
        Parameter para2(_T("FolderName"), _T("C:\\")); 

        pFolderCondition->GetParameterTable().AddParameter(para1);
        pFolderCondition->GetParameterTable().AddParameter(para2);
    }

    ActionPtr pSanityCheck = Action::Create( _T("ConditionListCheckAction"), GetWorkingBrain()->GetBehaviorManager());
    {

        Parameter para1(_T("IdList"), _T("{VerifyFolderCExist} {dummy}")); 
        pSanityCheck->GetParameterTable().AddParameter(para1);
    }

    bool bRet = pSanityCheck->Execute();
    EXPECT_EQ(false, bRet);

	GetWorkingBrain()->GetBehaviorManager()->UnregisterAction(pSanityCheck);
}
