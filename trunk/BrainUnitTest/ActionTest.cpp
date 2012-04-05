#include "StdAfx.h"
#include "TaskManager.h"

#define THIS_APP_NAME _T("BrainUnitTest.exe")

TEST(ActionTest, ConditionBlockAction)
{
	Condition procCondition(BrainApplication::GetWorkingBrain()->GetTaskManager(), _T("ProcessRunningCondition"));
	{
		Parameter para1(_T("ObjectId"), _T("IsUnitTest_exeRunning")); 
		procCondition.GetParameterTable().AddParameter(para1);

		Parameter para2(_T("ProcessName"), THIS_APP_NAME); 
		procCondition.GetParameterTable().AddParameter(para2);
	}

	
	Action blockAction(BrainApplication::GetWorkingBrain()->GetTaskManager(), _T("ConditionBlockAction"));
	{
		Parameter para1(_T("ConditionId"), _T("IsUnitTest_exeRunning")); 
		blockAction.GetParameterTable().AddParameter(para1);

		Parameter para2(_T("ExpectedResult"), _T("true")); 
		blockAction.GetParameterTable().AddParameter(para2);
	}

	bool bRet = blockAction.Execute();
	EXPECT_EQ(true, bRet);
}

// 
// A1: if(C) {Execute A2}
// A2: if(C) {Execute A1}
// Execute A2. Verify the loop below can be detected
TEST(ActionTest, ReferenceLoopAction)
{
	ApplicationSwitchHelper helper;

	{
		Condition *pC = new Condition(BrainApplication::GetWorkingBrain()->GetTaskManager(), _T("FolderExistsCondition"));
		Parameter para1(_T("ObjectId"), _T("C")); 
		Parameter para2(_T("FolderName"), _T("C:\\")); 
		pC->GetParameterTable().AddParameter(para1);
		pC->GetParameterTable().AddParameter(para2);
	}

	{
		Action *pA1 = new Action(BrainApplication::GetWorkingBrain()->GetTaskManager(), _T("ComplexAction"));
		Parameter para1(_T("ObjectId"), _T("A1")); 
		Parameter para2(_T("MainAction"), _T("A2"));
		Parameter para3(_T("ExecuteCondition"), _T("C"));
		pA1->GetParameterTable().AddParameter(para1);
		pA1->GetParameterTable().AddParameter(para2);
		pA1->GetParameterTable().AddParameter(para3);

	}

	Action A2(BrainApplication::GetWorkingBrain()->GetTaskManager(), _T("ComplexAction"));
	{
		Parameter para1(_T("ObjectId"), _T("A2")); 
		Parameter para2(_T("MainAction"), _T("A1"));
		Parameter para3(_T("ExecuteCondition"), _T("C"));
		A2.GetParameterTable().AddParameter(para1);
		A2.GetParameterTable().AddParameter(para2);
		A2.GetParameterTable().AddParameter(para3);
	}

	bool bRet = A2.Execute(); // The assert is expected.
	EXPECT_EQ(false, bRet);
}


TEST(ActionTest, RunProcessAction)
{

	Action processAction(BrainApplication::GetWorkingBrain()->GetTaskManager(), _T("RunProcessAction"));
	{
		Parameter para1(_T("ApplicationName"), _T("C:\\Windows\\System32\\notepad.exe")); 
		Parameter para2(_T("ApplicationParameter"), _T("")); 
		Parameter para3(_T("ShowWindow"), _T("true")); 
		Parameter para4(_T("WaitForExit"), _T("false")); 

		processAction.GetParameterTable().AddParameter(para1);
		processAction.GetParameterTable().AddParameter(para2);
		processAction.GetParameterTable().AddParameter(para3);
		processAction.GetParameterTable().AddParameter(para4);
	}

	bool bRet = processAction.Execute();
	EXPECT_EQ(true, bRet);
}

TEST(ActionTest, TaskListAction)
{
    ApplicationSwitchHelper helper;

    {
        Action* pAction = new Action(BrainApplication::GetWorkingBrain()->GetTaskManager(), _T("RunSystemCommandAction"));
        Parameter para0(_T("ObjectId"), _T("EchoMessage")); 
        Parameter para1(_T("ApplicationName"), _T("echo Hello world")); 
        Parameter para2(_T("ApplicationParameter"), _T("")); 


        pAction->GetParameterTable().AddParameter(para0);
        pAction->GetParameterTable().AddParameter(para1);
        pAction->GetParameterTable().AddParameter(para2);
    }

    Action taskList(BrainApplication::GetWorkingBrain()->GetTaskManager(), _T("TaskListAction"));
    {

        Parameter para1(_T("IdList"), _T("{EchoMessage}")); 
        taskList.GetParameterTable().AddParameter(para1);
    }

    bool bRet = taskList.Execute();

    EXPECT_EQ(true, bRet);
}

TEST(ActionTest, TaskListAction_2)
{
    ApplicationSwitchHelper helper;

    {
        Action* pAction = new Action(BrainApplication::GetWorkingBrain()->GetTaskManager(), _T("RunSystemCommandAction"));
        Parameter para0(_T("ObjectId"), _T("EchoMessage")); 
        Parameter para1(_T("ApplicationName"), _T("echo Hello world")); 
        Parameter para2(_T("ApplicationParameter"), _T("")); 


        pAction->GetParameterTable().AddParameter(para0);
        pAction->GetParameterTable().AddParameter(para1);
        pAction->GetParameterTable().AddParameter(para2);
    }

    Action taskList(BrainApplication::GetWorkingBrain()->GetTaskManager(), _T("TaskListAction"));
    {

        Parameter para1(_T("IdList"), _T("{EchoMessage}{DummyAction}")); 
        taskList.GetParameterTable().AddParameter(para1);
    }

    bool bRet = taskList.Execute();

    EXPECT_EQ(false, bRet);
}

TEST(ActionTest, ConditionListCheckAction_1)
{
    ApplicationSwitchHelper helper;

    {
        Condition* pFolderCondition = new Condition(BrainApplication::GetWorkingBrain()->GetTaskManager(), _T("FolderExistsCondition"));
        Parameter para1(_T("ObjectId"), _T("VerifyFolderCExist")); 
        Parameter para2(_T("FolderName"), _T("C:\\")); 

        pFolderCondition->GetParameterTable().AddParameter(para1);
        pFolderCondition->GetParameterTable().AddParameter(para2);
    }

    Action sanityCheck(BrainApplication::GetWorkingBrain()->GetTaskManager(), _T("ConditionListCheckAction"));
    {

        Parameter para1(_T("IdList"), _T("{VerifyFolderCExist}")); 
        sanityCheck.GetParameterTable().AddParameter(para1);
    }

    bool bRet = sanityCheck.Execute();
    EXPECT_EQ(true, bRet);
}

TEST(ActionTest, ConditionListCheckAction_2)
{
    ApplicationSwitchHelper helper;

    {
        Condition* pFolderCondition = new Condition(BrainApplication::GetWorkingBrain()->GetTaskManager(), _T("FolderExistsCondition"));
        Parameter para1(_T("ObjectId"), _T("VerifyFolderCExist")); 
        Parameter para2(_T("FolderName"), _T("C:\\")); 

        pFolderCondition->GetParameterTable().AddParameter(para1);
        pFolderCondition->GetParameterTable().AddParameter(para2);
    }

    {
        Condition* pFolderCondition = new Condition(BrainApplication::GetWorkingBrain()->GetTaskManager(), _T("FolderExistsCondition"));
        Parameter para1(_T("ObjectId"), _T("VerifyFolderZZExist")); 
        Parameter para2(_T("FolderName"), _T("ZZ:\\")); 

        pFolderCondition->GetParameterTable().AddParameter(para1);
        pFolderCondition->GetParameterTable().AddParameter(para2);
    }

    Action sanityCheck(BrainApplication::GetWorkingBrain()->GetTaskManager(), _T("ConditionListCheckAction"));
    {

        Parameter para1(_T("IdList"), _T("{VerifyFolderCExist} {VerifyFolderZZExist}")); 
        sanityCheck.GetParameterTable().AddParameter(para1);
    }

    bool bRet = sanityCheck.Execute();
    EXPECT_EQ(false, bRet);
}


TEST(ActionTest, ConditionListCheckAction_3)
{
    ApplicationSwitchHelper helper;

    {
        Condition* pFolderCondition = new Condition(BrainApplication::GetWorkingBrain()->GetTaskManager(), _T("FolderExistsCondition"));
        Parameter para1(_T("ObjectId"), _T("VerifyFolderCExist")); 
        Parameter para2(_T("FolderName"), _T("C:\\")); 

        pFolderCondition->GetParameterTable().AddParameter(para1);
        pFolderCondition->GetParameterTable().AddParameter(para2);
    }

    Action sanityCheck(BrainApplication::GetWorkingBrain()->GetTaskManager(), _T("ConditionListCheckAction"));
    {

        Parameter para1(_T("IdList"), _T("{VerifyFolderCExist} {dummy}")); 
        sanityCheck.GetParameterTable().AddParameter(para1);
    }

    bool bRet = sanityCheck.Execute();
    EXPECT_EQ(false, bRet);
}
