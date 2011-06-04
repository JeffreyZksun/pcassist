#include "StdAfx.h"
#include "TaskManager.h"
#include <algorithm>

//////////////////////////////////////////////////////////////////////////
// TaskManager
//////////////////////////////////////////////////////////////////////////

TaskManager::TaskManager(void)
    : mRegisteredActions(), mRegisteredContions(), mTaskList()
{
}

TaskManager::~TaskManager(void)
{
    deleteRegisteredActions();
    deleteRegisteredConditions();

    // All the tasks should be registered actions.
    ASSERT(mTaskList.empty());
}

TaskManager* TaskManager::Get()
{
    static TaskManager singleton;
    return &singleton;
}

void TaskManager::RegisterAction(Action* pAction)
{
    ASSERT(pAction != NULL);
    if(NULL == pAction)
        return;

    ActionList::iterator it = std::find(mRegisteredActions.begin(), mRegisteredActions.end(), pAction);
    ASSERT(mRegisteredActions.end() == it);

    if(mRegisteredActions.end() == it) // not exist
        mRegisteredActions.push_back(pAction);

}

void TaskManager::UnregisterAction(Action* pAction)
{
    ActionList::iterator it = std::find(mRegisteredActions.begin(), mRegisteredActions.end(), pAction);

    if(mRegisteredActions.end() != it) // exist
    {
        mRegisteredActions.remove(pAction);
        RemoveActionTask(pAction);
    }
}

void TaskManager::RegisterCondition(Condition* pCondition)
{
    ASSERT(pCondition != NULL);
    if(NULL == pCondition)
        return;

    ConditionList::iterator it = std::find(mRegisteredContions.begin(), mRegisteredContions.end(), pCondition);
    ASSERT(mRegisteredContions.end() == it);

    if(mRegisteredContions.end() == it) // not exist
        mRegisteredContions.push_back(pCondition);
}

void TaskManager::UnregisterCondition(Condition* pCondition)
{
    ConditionList::iterator it = std::find(mRegisteredContions.begin(), mRegisteredContions.end(), pCondition);

    if(mRegisteredContions.end() != it) // exist
        mRegisteredContions.remove(pCondition);
}

void TaskManager::AddActionTask(Action* pAction)
{
    ASSERT(pAction != NULL);
    if(NULL == pAction)
        return;

    ActionList::iterator it = std::find(mTaskList.begin(), mTaskList.end(), pAction);
    ASSERT(mTaskList.end() == it);

    if(mTaskList.end() == it) // not exist
        mTaskList.push_back(pAction);
}

void TaskManager::RemoveActionTask(Action* pAction)
{
    ActionList::iterator it = std::find(mTaskList.begin(), mTaskList.end(), pAction);

    if(mTaskList.end() != it) // exist
        mTaskList.remove(pAction);
}

bool TaskManager::RunTasks()
{
    bool bRet = true;
    for (ActionList::iterator it = mTaskList.begin(); it != mTaskList.end(); ++it)
    {
        ASSERT(*it != NULL);
        bRet = (*it)->Execute();
    }

    return bRet;
}
void TaskManager::deleteRegisteredActions()
{
    ActionList::iterator it = mRegisteredActions.begin();
    while(!mRegisteredActions.empty())
    {
        delete *it; // In its destructor, it will unregister itself from the list.
        it = mRegisteredActions.begin();
    }
}

void TaskManager::deleteRegisteredConditions()
{
    ConditionList::iterator it = mRegisteredContions.begin();
    while(!mRegisteredContions.empty())
    {
        delete *it; // In its destructor, it will unregister itself from the list.
        it = mRegisteredContions.begin();
    }
}

//////////////////////////////////////////////////////////////////////////
// Action
//////////////////////////////////////////////////////////////////////////

Action::Action(void)
{
    TaskManager* pTaskMgr = TaskManager::Get();
    pTaskMgr->RegisterAction(this);
}

Action::~Action(void)
{
    TaskManager* pTaskMgr = TaskManager::Get();
    pTaskMgr->UnregisterAction(this);
}

//////////////////////////////////////////////////////////////////////////
// Condition
//////////////////////////////////////////////////////////////////////////

Condition::Condition(void)
{
    TaskManager* pTaskMgr = TaskManager::Get();
    pTaskMgr->RegisterCondition(this);
}

Condition::~Condition(void)
{
    TaskManager* pTaskMgr = TaskManager::Get();
    pTaskMgr->UnregisterCondition(this);
}
