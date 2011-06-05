#include "StdAfx.h"
#include "TaskManager.h"
#include <algorithm>
#include "ConstantsDefinition.h"

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

	// Check if there is name conflict. We can't cached the ids in this class. 
	// Because the object id can be changed at any time.
	// So we need to traverse the list every time.

	CString objectID = pAction->GetObjectId();
	for(ActionList::const_iterator it = mRegisteredActions.begin(); it != mRegisteredActions.end(); ++it)
	{
		Action* pAction = *it;

		int iDiff = pAction->GetObjectId().CompareNoCase(objectID);
		if(0 == iDiff)  //exist
		{
			ASSERT(false);
			// ToDo - output error message.
			return;
		}
	}

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

Action*	TaskManager::GetActionById(const CString& objectID) const
{
	for(ActionList::const_iterator it = mRegisteredActions.begin(); it != mRegisteredActions.end(); ++it)
	{
		Action* pAction = *it;

		int iDiff = pAction->GetObjectId().CompareNoCase(objectID);
		if(0 == iDiff)
			return pAction;
	}

	return NULL;
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

Condition* TaskManager::GetConditionById(const CString& objectID) const
{
	for(ConditionList::const_iterator it = mRegisteredContions.begin(); it != mRegisteredContions.end(); ++it)
	{
		Condition* pCondition = *it;

		int iDiff = pCondition->GetObjectId().CompareNoCase(objectID);
		if(0 == iDiff)
			return pCondition;
	}

	return NULL;
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
// BehaviorNode
//////////////////////////////////////////////////////////////////////////

BehaviorNode::BehaviorNode(const CString& objetType)
{
	int address = (int)this;
	CString objectId;
	objectId.Format(_T("%d"), address);
	AddParameter(Parameter(OBJECT_ID, objectId));	// Used for query the object
	AddParameter(Parameter(OBJECT_TYPE, objetType));// Used for create the object by type.
}

CString BehaviorNode::GetObjectId() const
{
	Parameter para;
	bool bExist = GetParameter(OBJECT_ID, para);
	ASSERT(bExist);
	if(!bExist)
		return _T("");

	return para.GetEvaluatedValue();
}

CString BehaviorNode::GetObjectType() const
{
	Parameter para;
	bool bExist = GetParameter(OBJECT_TYPE, para);
	ASSERT(bExist);
	if(!bExist)
		return _T("");

	return para.GetEvaluatedValue();
}

//////////////////////////////////////////////////////////////////////////
// Action
//////////////////////////////////////////////////////////////////////////

Action::Action(const CString& objetType)
	: BehaviorNode(objetType)
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

Condition::Condition(const CString& objetType)
	: BehaviorNode(objetType)
{
    TaskManager* pTaskMgr = TaskManager::Get();
    pTaskMgr->RegisterCondition(this);
}

Condition::~Condition(void)
{
    TaskManager* pTaskMgr = TaskManager::Get();
    pTaskMgr->UnregisterCondition(this);
}
