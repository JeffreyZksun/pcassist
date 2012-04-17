#include "StdAfx.h"

using namespace Ts;

TEST(TaskTest, ImmediateTaskBasic)
{
	ITaskSystemPtr pTaskSystem (new TaskSystem());
	Ts::ITaskManagerPtr pTaskMgr = pTaskSystem->GetTaskManager();

	EXPECT_EQ(true, pTaskMgr != NULL);

	{
		ImmediateTask::pointer pTask (ImmediateTask::Create(_T("tempTask")));
		EXPECT_EQ(true, pTask != NULL);

		const WString taskId = pTask->GetId();
		EXPECT_EQ(_T("tempTask"), taskId);

		const bool bIsReady = pTask->IsReady(pTaskSystem.get());
		EXPECT_EQ(true, bIsReady);

		size_t count = pTask->GetActionCount();
		EXPECT_EQ(0, count);

		pTask->AppendAction(_T("TestAction"));

		count = pTask->GetActionCount();
		EXPECT_EQ(1, count);
	}
}


TEST(TaskTest, ImmediateTaskExecute)
{
	ITaskSystemPtr pTaskSystem (new TaskSystem());
	Ts::ITaskManagerPtr pTaskMgr = pTaskSystem->GetTaskManager();

	EXPECT_EQ(true, pTaskMgr != NULL);

	{
		BehaviorManager* pBehaviorManager = pTaskSystem->GetBehaviorManager();

		WString actionName = _T("demoAction");
		Action* pNewAction = new Action(pBehaviorManager, _T("EmptyAction"));
		pNewAction->GetParameterTable().AddParameter(Parameter(OBJECT_ID, actionName.data()));

		ImmediateTask::pointer pTask (ImmediateTask::Create(_T("tempTask")));
		EXPECT_EQ(true, pTask != NULL);

		pTask->AppendAction(actionName);

		const bool ok = pTask->Execute(pTaskSystem.get());
		EXPECT_EQ(true, ok);
	}
}

TEST(TaskTest, ConditionalTaskBasic)
{
	ITaskSystemPtr pTaskSystem (new TaskSystem());
	Ts::ITaskManagerPtr pTaskMgr = pTaskSystem->GetTaskManager();

	EXPECT_EQ(true, pTaskMgr != NULL);

	{
		WString conditionName (_T("TrueCondition"));
		ImmediateTask::pointer pImmeTask (ImmediateTask::Create(_T("basicTask")));
		ConditionalTask::pointer pTask (ConditionalTask::Create(_T("conditionTask"), conditionName, pImmeTask));
		EXPECT_EQ(true, pTask != NULL);

		const WString taskId = pTask->GetId();
		EXPECT_EQ(_T("conditionTask"), taskId);

		bool bIsReady = pTask->IsReady(pTaskSystem.get());
		EXPECT_EQ(false, bIsReady);

		BehaviorManager* pBehaviorManager = pTaskSystem->GetBehaviorManager();

		Condition* pNewCondtion = new Condition(pBehaviorManager, _T("TrueCondition"));
		pNewCondtion->GetParameterTable().AddParameter(Parameter(OBJECT_ID, conditionName.data()));

		bIsReady = pTask->IsReady(pTaskSystem.get());
		EXPECT_EQ(true, bIsReady);
	}
}

TEST(TaskTest, ConditionalTaskExecute)
{
	ITaskSystemPtr pTaskSystem (new TaskSystem());
	Ts::ITaskManagerPtr pTaskMgr = pTaskSystem->GetTaskManager();

	EXPECT_EQ(true, pTaskMgr != NULL);

	{
		BehaviorManager* pBehaviorManager = pTaskSystem->GetBehaviorManager();

		WString actionName = _T("demoAction");
		Action* pNewAction = new Action(pBehaviorManager, _T("EmptyAction"));
		pNewAction->GetParameterTable().AddParameter(Parameter(OBJECT_ID, actionName.data()));

		WString conditionName (_T("TrueCondition"));
		Condition* pNewCondtion = new Condition(pBehaviorManager, _T("TrueCondition"));
		pNewCondtion->GetParameterTable().AddParameter(Parameter(OBJECT_ID, conditionName.data()));
		
		ImmediateTask::pointer pImmeTask (ImmediateTask::Create(_T("basicTask")));
		pImmeTask->AppendAction(actionName);

		ConditionalTask::pointer pTask (ConditionalTask::Create(_T("conditionTask"), conditionName, pImmeTask));

		const bool ok = pTask->Execute(pTaskSystem.get());
		EXPECT_EQ(true, ok);
	}
}

