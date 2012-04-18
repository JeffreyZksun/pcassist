#include "StdAfx.h"

TEST(TaskManagerTest, RegisterUnregister)
{
	ITaskSystemPtr pTaskSystem (new TaskSystem());
	Ts::ITaskManagerPtr pTaskMgr = pTaskSystem->GetTaskManager();

	{
		{
			size_t count = pTaskMgr->RegisteredTaskCount();
			EXPECT_EQ(0, count);
		}

		WString actionName = _T("demoAction");
		{
			BehaviorManager* pBehaviorManager = pTaskSystem->GetBehaviorManager();

			ActionPtr pNewAction = Action::Create(_T("EmptyAction"), pBehaviorManager);
			pNewAction->GetParameterTable().AddParameter(Parameter(OBJECT_ID, actionName.data()));
		}

		ImmediateTask::pointer pTask (ImmediateTask::Create(_T("tempTask")));
		{
			EXPECT_EQ(true, pTask != NULL);

			pTask->AppendAction(actionName);
			bool ok = pTaskMgr->RegisterTask(pTask);
			EXPECT_EQ(true, ok);
		}

		{
			size_t count = pTaskMgr->RegisteredTaskCount();
			EXPECT_EQ(1, count);
		}

		{
			ImmediateTask::pointer pTask2 (ImmediateTask::Create(_T("tempTask")));
			EXPECT_EQ(true, pTask2 != NULL);

			pTask->AppendAction(actionName);
			bool ok = pTaskMgr->RegisterTask(pTask2); // Add one with duplicated name
			EXPECT_EQ(false, ok);
		}

		{
			size_t count = pTaskMgr->RegisteredTaskCount();
			EXPECT_EQ(1, count);
		}

		ImmediateTask::pointer pTask3 (ImmediateTask::Create(_T("tempTask2")));
		{
			EXPECT_EQ(true, pTask3 != NULL);

			pTask->AppendAction(actionName);
			bool ok = pTaskMgr->RegisterTask(pTask3); // Add the second one
			EXPECT_EQ(true, ok);
		}

		{
			size_t count = pTaskMgr->RegisteredTaskCount();
			EXPECT_EQ(2, count);
		}

		{
			bool ok = pTaskMgr->UnregisterTask(pTask);
			EXPECT_EQ(true, ok);
		}

		{
			size_t count = pTaskMgr->RegisteredTaskCount();
			EXPECT_EQ(1, count);
		}

		{
			ImmediateTask::pointer pNoExistingTask (ImmediateTask::Create(_T("NoExistingTask")));
			EXPECT_EQ(true, pNoExistingTask != NULL);

			bool ok = pTaskMgr->UnregisterTask(pNoExistingTask);
			EXPECT_EQ(false, ok);
		}

		{
			size_t count = pTaskMgr->RegisteredTaskCount();
			EXPECT_EQ(1, count);
		}

		{
			bool ok = pTaskMgr->UnregisterTask(pTask3);
			EXPECT_EQ(true, ok);
		}

		{
			size_t count = pTaskMgr->RegisteredTaskCount();
			EXPECT_EQ(0, count);
		}
	}
}

TEST(TaskManagerTest, AddRemove)
{
	ITaskSystemPtr pTaskSystem (new TaskSystem());
	Ts::ITaskManagerPtr pTaskMgr = pTaskSystem->GetTaskManager();

	{
		{
			size_t count = pTaskMgr->PendingTaskCount();
			EXPECT_EQ(0, count);
		}

		WString taskid1 = _T("tempTask1");
		WString taskid2 = _T("tempTask2");

		pTaskMgr->AddTask(taskid1); 

		{
			size_t count = pTaskMgr->PendingTaskCount();
			EXPECT_EQ(1, count);
		}

		pTaskMgr->AddTask(taskid1); 

		{
			size_t count = pTaskMgr->PendingTaskCount();
			EXPECT_EQ(2, count);
		}

		pTaskMgr->AddTask(taskid2); 

		{
			size_t count = pTaskMgr->PendingTaskCount();
			EXPECT_EQ(3, count);
		}

		pTaskMgr->RemoveTask(taskid1); 

		{
			size_t count = pTaskMgr->PendingTaskCount();
			EXPECT_EQ(1, count);
		}

		pTaskMgr->RemoveTask(taskid2); 

		{
			size_t count = pTaskMgr->PendingTaskCount();
			EXPECT_EQ(0, count);
		}

		pTaskMgr->RemoveTask(taskid2); 

		{
			size_t count = pTaskMgr->PendingTaskCount();
			EXPECT_EQ(0, count);
		}
	}
}


TEST(TaskManagerTest, GetTaskById)
{
	ITaskSystemPtr pTaskSystem (new TaskSystem());
	Ts::ITaskManagerPtr pTaskMgr = pTaskSystem->GetTaskManager();

	{

		ImmediateTask::pointer pTask1 (ImmediateTask::Create(_T("tempTask1")));
		{
			EXPECT_EQ(true, pTask1 != NULL);

			bool ok = pTaskMgr->RegisterTask(pTask1);
			EXPECT_EQ(true, ok);
		}

		ImmediateTask::pointer pTask2 (ImmediateTask::Create(_T("tempTask2")));
		{
			EXPECT_EQ(true, pTask1 != NULL);

			bool ok = pTaskMgr->RegisterTask(pTask2);
			EXPECT_EQ(true, ok);
		}

		{
			ITaskPtr pTask = pTaskMgr->GetTaskById(_T("tempTask1"));
			ImmediateTask::pointer pImmediTask =  boost::dynamic_pointer_cast<ImmediateTask>(pTask);
			EXPECT_EQ(true, pImmediTask.get() == pTask1.get());
		}

		{
			ITaskPtr pTask = pTaskMgr->GetTaskById(_T("tempTask2"));
			ImmediateTask::pointer pImmediTask =  boost::dynamic_pointer_cast<ImmediateTask>(pTask);
			EXPECT_EQ(true, pImmediTask.get() == pTask2.get());
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
			size_t count = pTaskMgr->PendingTaskCount();
			EXPECT_EQ(0, count);
		}

		// Add action
		WString actionName = _T("demoAction");
		{
			BehaviorManager* pBehaviorManager = pTaskSystem->GetBehaviorManager();
			
			ActionPtr pNewAction = Action::Create(_T("EmptyAction"), pBehaviorManager);
			pNewAction->GetParameterTable().AddParameter(Parameter(OBJECT_ID, actionName.data()));
		}

		// Register and add a task
		{
			ImmediateTask::pointer pTask (ImmediateTask::Create(_T("tempTask")));
			EXPECT_EQ(true, pTask != NULL);

			pTask->AppendAction(actionName);
			pTaskMgr->RegisterTask(pTask);
			pTaskMgr->AddTask(pTask->GetObjectId());
		}

		{
			size_t count = pTaskMgr->PendingTaskCount();
			EXPECT_EQ(1, count);
		}

		{
			size_t count = pTaskMgr->PollOne();
			EXPECT_EQ(1, count);
		}

		{
			size_t count = pTaskMgr->PendingTaskCount();
			EXPECT_EQ(0, count);
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

			ActionPtr pNewAction = Action::Create(_T("EmptyAction"), pBehaviorManager);
			pNewAction->GetParameterTable().AddParameter(Parameter(OBJECT_ID, actionName.data()));
		}

		{
			ImmediateTask::pointer pTask (ImmediateTask::Create(_T("tempTask")));
			EXPECT_EQ(true, pTask != NULL);

			pTask->AppendAction(actionName);
			pTaskMgr->RegisterTask(pTask);
			pTaskMgr->AddTask(pTask->GetObjectId());
		}

		{
			ImmediateTask::pointer pTask (ImmediateTask::Create(_T("tempTask2")));
			EXPECT_EQ(true, pTask != NULL);

			pTask->AppendAction(actionName);
			pTaskMgr->RegisterTask(pTask);
			pTaskMgr->AddTask(pTask->GetObjectId());
		}
		
		{
			size_t count = pTaskMgr->PendingTaskCount();
			EXPECT_EQ(2, count);
		}

		{
			size_t count = pTaskMgr->PollOne();
			EXPECT_EQ(1, count);
		}

		{
			size_t count = pTaskMgr->PendingTaskCount();
			EXPECT_EQ(1, count);
		}

		{
			size_t count = pTaskMgr->PollOne();
			EXPECT_EQ(1, count);
		}

		{
			size_t count = pTaskMgr->PendingTaskCount();
			EXPECT_EQ(0, count);
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

			ActionPtr pNewAction = Action::Create(_T("EmptyAction"), pBehaviorManager);
			pNewAction->GetParameterTable().AddParameter(Parameter(OBJECT_ID, actionName.data()));
		}

		{
			ImmediateTask::pointer pTask (ImmediateTask::Create(_T("tempTask")));
			EXPECT_EQ(true, pTask != NULL);

			pTask->AppendAction(actionName);
			pTaskMgr->RegisterTask(pTask);
			pTaskMgr->AddTask(pTask->GetObjectId());
		}

		{
			ImmediateTask::pointer pTask (ImmediateTask::Create(_T("tempTask2")));
			EXPECT_EQ(true, pTask != NULL);

			pTask->AppendAction(actionName);
			pTaskMgr->RegisterTask(pTask);
			pTaskMgr->AddTask(pTask->GetObjectId());
		}

		{
			size_t count = pTaskMgr->PendingTaskCount();
			EXPECT_EQ(2, count);
		}

		{
			size_t count = pTaskMgr->Poll();
			EXPECT_EQ(2, count);
		}

		{
			size_t count = pTaskMgr->PendingTaskCount();
			EXPECT_EQ(0, count);
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

			ActionPtr pNewAction = Action::Create(_T("EmptyAction"), pBehaviorManager);
			pNewAction->GetParameterTable().AddParameter(Parameter(OBJECT_ID, actionName.data()));
		}

		WString conditionName (_T("PreCondition"));
		{
			BehaviorManager* pBehaviorManager = pTaskSystem->GetBehaviorManager();

			ConditionPtr pNewCondtion = Condition::Create(_T("FalseCondition"), pBehaviorManager);
			pNewCondtion->GetParameterTable().AddParameter(Parameter(OBJECT_ID, conditionName.data()));
		}

		{
			ImmediateTask::pointer pImmeTask (ImmediateTask::Create(_T("basicTask")));
			pImmeTask->AppendAction(actionName);
			pTaskMgr->RegisterTask(pImmeTask);
			
			ConditionalTask::pointer pTask (ConditionalTask::Create(_T("conditionTask"), conditionName, pImmeTask->GetObjectId()));
			pTaskMgr->RegisterTask(pTask);

			pTaskMgr->AddTask(pImmeTask->GetObjectId());
			pTaskMgr->AddTask(pTask->GetObjectId());
		}

		{
			size_t count = pTaskMgr->PendingTaskCount();
			EXPECT_EQ(2, count);
		}

		{
			size_t count = pTaskMgr->Poll();
			EXPECT_EQ(1, count);
		}

		{
			size_t count = pTaskMgr->PendingTaskCount();
			EXPECT_EQ(1, count);
		}

		{
			size_t count = pTaskMgr->PollOne();
			EXPECT_EQ(0, count);
		}

		{
			size_t count = pTaskMgr->PendingTaskCount();
			EXPECT_EQ(1, count);
		}
	}
}


TEST(TaskManagerTest, StartStop)
{
	ITaskSystemPtr pTaskSystem (new TaskSystem());
	Ts::ITaskManagerPtr pTaskMgr = pTaskSystem->GetTaskManager();

	{
		pTaskMgr->Start();
		pTaskMgr->Stop();
	}
}
