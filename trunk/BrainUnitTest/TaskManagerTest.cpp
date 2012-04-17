#include "StdAfx.h"

TEST(TaskManagerTest, AddRemove)
{
	ITaskSystemPtr pTaskSystem (new TaskSystem());
	Ts::ITaskManagerPtr pTaskMgr = pTaskSystem->GetTaskManager();

	{
		{
			size_t pendingCount = pTaskMgr->PendingTaskCount();
			EXPECT_EQ(0, pendingCount);
		}

		WString actionName = _T("demoAction");
		{
			BehaviorManager* pBehaviorManager = pTaskSystem->GetBehaviorManager();

			Action* pNewAction = new Action(pBehaviorManager, _T("EmptyAction"));
			pNewAction->GetParameterTable().AddParameter(Parameter(OBJECT_ID, actionName.data()));
		}

		{
			ImmediateTask::pointer pTask (ImmediateTask::Create(_T("tempTask")));
			EXPECT_EQ(true, pTask != NULL);

			pTask->AppendAction(actionName);
			bool ok = pTaskMgr->AddTask(pTask);
			EXPECT_EQ(true, ok);
		}

		{
			size_t pendingCount = pTaskMgr->PendingTaskCount();
			EXPECT_EQ(1, pendingCount);
		}

		{
			ImmediateTask::pointer pTask (ImmediateTask::Create(_T("tempTask")));
			EXPECT_EQ(true, pTask != NULL);

			pTask->AppendAction(actionName);
			bool ok = pTaskMgr->AddTask(pTask); // Add duplicated one
			EXPECT_EQ(false, ok);
		}

		{
			size_t pendingCount = pTaskMgr->PendingTaskCount();
			EXPECT_EQ(1, pendingCount);
		}

		{
			ImmediateTask::pointer pTask (ImmediateTask::Create(_T("tempTask2")));
			EXPECT_EQ(true, pTask != NULL);

			pTask->AppendAction(actionName);
			bool ok = pTaskMgr->AddTask(pTask); // Add the second one
			EXPECT_EQ(true, ok);
		}

		{
			size_t pendingCount = pTaskMgr->PendingTaskCount();
			EXPECT_EQ(2, pendingCount);
		}

		{
			bool ok = pTaskMgr->RemoveTask(_T("tempTask2"));
			EXPECT_EQ(true, ok);
		}

		{
			bool ok = pTaskMgr->RemoveTask(_T("NotExitingTask"));
			EXPECT_EQ(false, ok);
		}

		{
			bool ok = pTaskMgr->RemoveTask(_T("tempTask"));
			EXPECT_EQ(true, ok);
		}

		{
			size_t pendingCount = pTaskMgr->PendingTaskCount();
			EXPECT_EQ(0, pendingCount);
		}
	}
}

TEST(TaskManagerTest, PollOne)
{
	ITaskSystemPtr pTaskSystem (new TaskSystem());
	Ts::ITaskManagerPtr pTaskMgr = pTaskSystem->GetTaskManager();

	{
		{
			size_t count = pTaskMgr->PollOne();
			EXPECT_EQ(0, count);
		}

		{
			size_t pendingCount = pTaskMgr->PendingTaskCount();
			EXPECT_EQ(0, pendingCount);
		}

		WString actionName = _T("demoAction");
		{
			BehaviorManager* pBehaviorManager = pTaskSystem->GetBehaviorManager();
			
			Action* pNewAction = new Action(pBehaviorManager, _T("EmptyAction"));
			pNewAction->GetParameterTable().AddParameter(Parameter(OBJECT_ID, actionName.data()));
		}

		{
			ImmediateTask::pointer pTask (ImmediateTask::Create(_T("tempTask")));
			EXPECT_EQ(true, pTask != NULL);

			pTask->AppendAction(actionName);
			pTaskMgr->AddTask(pTask);
		}

		{
			size_t pendingCount = pTaskMgr->PendingTaskCount();
			EXPECT_EQ(1, pendingCount);
		}

		{
			size_t count = pTaskMgr->PollOne();
			EXPECT_EQ(1, count);
		}

		{
			size_t pendingCount = pTaskMgr->PendingTaskCount();
			EXPECT_EQ(0, pendingCount);
		}

		{
			size_t count = pTaskMgr->PollOne();
			EXPECT_EQ(0, count);
		}

	}
}

TEST(TaskManagerTest, PollOne2)
{
	ITaskSystemPtr pTaskSystem (new TaskSystem());
	Ts::ITaskManagerPtr pTaskMgr = pTaskSystem->GetTaskManager();

	{
		WString actionName = _T("demoAction");
		{
			BehaviorManager* pBehaviorManager = pTaskSystem->GetBehaviorManager();

			Action* pNewAction = new Action(pBehaviorManager, _T("EmptyAction"));
			pNewAction->GetParameterTable().AddParameter(Parameter(OBJECT_ID, actionName.data()));
		}

		{
			ImmediateTask::pointer pTask (ImmediateTask::Create(_T("tempTask")));
			EXPECT_EQ(true, pTask != NULL);

			pTask->AppendAction(actionName);
			pTaskMgr->AddTask(pTask);
		}

		{
			ImmediateTask::pointer pTask (ImmediateTask::Create(_T("tempTask2")));
			EXPECT_EQ(true, pTask != NULL);

			pTask->AppendAction(actionName);
			pTaskMgr->AddTask(pTask);
		}
		
		{
			size_t pendingCount = pTaskMgr->PendingTaskCount();
			EXPECT_EQ(2, pendingCount);
		}

		{
			size_t count = pTaskMgr->PollOne();
			EXPECT_EQ(1, count);
		}

		{
			size_t pendingCount = pTaskMgr->PendingTaskCount();
			EXPECT_EQ(1, pendingCount);
		}

		{
			size_t count = pTaskMgr->PollOne();
			EXPECT_EQ(1, count);
		}

		{
			size_t pendingCount = pTaskMgr->PendingTaskCount();
			EXPECT_EQ(0, pendingCount);
		}
	}
}

TEST(TaskManagerTest, Poll)
{
	ITaskSystemPtr pTaskSystem (new TaskSystem());
	Ts::ITaskManagerPtr pTaskMgr = pTaskSystem->GetTaskManager();

	{
		WString actionName = _T("demoAction");
		{
			BehaviorManager* pBehaviorManager = pTaskSystem->GetBehaviorManager();

			Action* pNewAction = new Action(pBehaviorManager, _T("EmptyAction"));
			pNewAction->GetParameterTable().AddParameter(Parameter(OBJECT_ID, actionName.data()));
		}

		{
			ImmediateTask::pointer pTask (ImmediateTask::Create(_T("tempTask")));
			EXPECT_EQ(true, pTask != NULL);

			pTask->AppendAction(actionName);
			pTaskMgr->AddTask(pTask);
		}

		{
			ImmediateTask::pointer pTask (ImmediateTask::Create(_T("tempTask2")));
			EXPECT_EQ(true, pTask != NULL);

			pTask->AppendAction(actionName);
			pTaskMgr->AddTask(pTask);
		}

		{
			size_t pendingCount = pTaskMgr->PendingTaskCount();
			EXPECT_EQ(2, pendingCount);
		}

		{
			size_t count = pTaskMgr->Poll();
			EXPECT_EQ(2, count);
		}

		{
			size_t pendingCount = pTaskMgr->PendingTaskCount();
			EXPECT_EQ(0, pendingCount);
		}
	}
}

TEST(TaskManagerTest, PollOneConditionalTask)
{
	ITaskSystemPtr pTaskSystem (new TaskSystem());
	Ts::ITaskManagerPtr pTaskMgr = pTaskSystem->GetTaskManager();

	{
		WString actionName = _T("demoAction");
		{
			BehaviorManager* pBehaviorManager = pTaskSystem->GetBehaviorManager();

			Action* pNewAction = new Action(pBehaviorManager, _T("EmptyAction"));
			pNewAction->GetParameterTable().AddParameter(Parameter(OBJECT_ID, actionName.data()));
		}

		WString conditionName (_T("PreCondition"));
		{
			BehaviorManager* pBehaviorManager = pTaskSystem->GetBehaviorManager();

			Condition* pNewCondtion = new Condition(pBehaviorManager, _T("FalseCondition"));
			pNewCondtion->GetParameterTable().AddParameter(Parameter(OBJECT_ID, conditionName.data()));
		}

		{
			ImmediateTask::pointer pImmeTask (ImmediateTask::Create(_T("basicTask")));
			pImmeTask->AppendAction(actionName);
			
			ConditionalTask::pointer pTask (ConditionalTask::Create(_T("conditionTask"), conditionName, pImmeTask));

			pTaskMgr->AddTask(pImmeTask);
			pTaskMgr->AddTask(pTask);
		}

		{
			size_t pendingCount = pTaskMgr->PendingTaskCount();
			EXPECT_EQ(2, pendingCount);
		}

		{
			size_t count = pTaskMgr->Poll();
			EXPECT_EQ(1, count);
		}

		{
			size_t pendingCount = pTaskMgr->PendingTaskCount();
			EXPECT_EQ(1, pendingCount);
		}

		{
			size_t count = pTaskMgr->PollOne();
			EXPECT_EQ(0, count);
		}

		{
			size_t pendingCount = pTaskMgr->PendingTaskCount();
			EXPECT_EQ(1, pendingCount);
		}
	}
}
