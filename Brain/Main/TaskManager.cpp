#include "StdAfx.h"
#include "TaskManager.h"
#include <algorithm>
#include "ConstantsDefinition.h"
#include "XmlIOStream.h"

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

bool TaskManager::RegisterAction(Action* pAction)
{
	return _RegisterBehaviorNode(mRegisteredActions, pAction);
}

void TaskManager::UnregisterAction(Action* pAction)
{
    _UnregisterBehaviorNode(mRegisteredActions, pAction);

	RemoveActionTask(pAction);
}

Action*	TaskManager::GetActionById(const CString& objectId) const
{
	BehaviorNode* pNode = _GetBehaviorNodeById(mRegisteredActions, objectId);

	Action* pAction = NULL;
	if(pNode != NULL)
		pAction = dynamic_cast<Action*>(pNode);

	return pAction;
}

bool TaskManager::RegisterCondition(Condition* pCondition)
{
	return _RegisterBehaviorNode(mRegisteredContions, pCondition);
}

void TaskManager::UnregisterCondition(Condition* pCondition)
{
    _UnregisterBehaviorNode(mRegisteredContions, pCondition);
}

Condition* TaskManager::GetConditionById(const CString& objectId) const
{
	BehaviorNode* pNode = _GetBehaviorNodeById(mRegisteredContions, objectId);

	Condition* pCondition = NULL;
	if(pNode != NULL)
		pCondition = dynamic_cast<Condition*>(pNode);

	return pCondition;
}

void TaskManager::AddActionTask(Action* pAction)
{
    ASSERT(pAction != NULL);
    if(NULL == pAction)
        return;

    //ActionList::iterator it = std::find(mTaskList.begin(), mTaskList.end(), pAction);
    //ASSERT(mTaskList.end() == it);

	// The same action can be added more than once. Don't need the duplication check.
    mTaskList.push_back(pAction);
}

void TaskManager::RemoveActionTask(Action* pAction)
{
    ActionList::iterator it = std::find(mTaskList.begin(), mTaskList.end(), pAction);

    while(mTaskList.end() != it) // exist
	{
        mTaskList.remove(pAction);
		it = std::find(mTaskList.begin(), mTaskList.end(), pAction);
	}
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


/************************************************************************
 The data format is:
 
 <TaskList>
	<ActionId> (action id) </ActionId>
	<ActionId>...</ActionId>
	<ActionId>...</ActionId>
	...
 </TaskList>

 <Actions>
	 <Action> 
		<Parameter>...</Parameter>
		<Parameter>...</Parameter>
		...
	 </Action>
	 <Action>...</Action>
	 <Action>...</Action>
 ...
 </Actions>

 <Conditions>
	 <Condition> 
		 <Parameter>...</Parameter>
		 <Parameter>...</Parameter>
	 ...
	 </Condition>
	 <Condition>...</Condition>
	 <Condition>...</Condition>
	...
 </Conditions>
************************************************************************/
bool TaskManager::XmlIn(XmlIOStream* pXmlIOStream)
{
	ASSERT(pXmlIOStream != NULL);
	return true;
}

bool TaskManager::XmlOut(XmlIOStream* pXmlIOStream) const
{
	ASSERT(pXmlIOStream != NULL);

	// TaskList
	{
		XmlIOStreamBeginNodeStack stack(pXmlIOStream, _T("TaskList"));

		for (ActionList::const_iterator it = mTaskList.begin(); it != mTaskList.end(); ++it)
		{
			ASSERT(*it != NULL);
			XmlIOStreamBeginNodeStack stack2(pXmlIOStream, _T("ActionId"));
			pXmlIOStream->SetNodeText((*it)->GetObjectId());
		}
	}

	// Actions
	{
		XmlIOStreamBeginNodeStack stack(pXmlIOStream, _T("Actions"));

		for (BehaviorNodeList::const_iterator it = mRegisteredActions.begin(); it != mRegisteredActions.end(); ++it)
		{
			ASSERT(*it != NULL);
			(*it)->XmlOut(pXmlIOStream);
		}
	}

	//Conditions
	{
		XmlIOStreamBeginNodeStack stack(pXmlIOStream, _T("Conditions"));

		for (BehaviorNodeList::const_iterator it = mRegisteredContions.begin(); it != mRegisteredContions.end(); ++it)
		{
			ASSERT(*it != NULL);
			(*it)->XmlOut(pXmlIOStream);
		}
	}

	return true;
}

void TaskManager::deleteRegisteredActions()
{
	_DeleteBehaviorNodes(mRegisteredActions);
}

void TaskManager::deleteRegisteredConditions()
{
	_DeleteBehaviorNodes(mRegisteredContions);
}

bool TaskManager::_RegisterBehaviorNode(BehaviorNodeList& nodeList, BehaviorNode* pNode)
{
	ASSERT(pNode != NULL);
	if(NULL == pNode)
		return false;

	// Check if there is name conflict. We can't cached the ids in this class. 
	// Because the object id can be changed at any time.
	// So we need to traverse the list every time.

	CString objectID = pNode->GetObjectId();
	for(BehaviorNodeList::const_iterator it = nodeList.begin(); it != nodeList.end(); ++it)
	{
		BehaviorNode* pAction = *it;

		int iDiff = pAction->GetObjectId().CompareNoCase(objectID);
		if(0 == iDiff)  //exist
		{
			ASSERT(false);
			// ToDo - output error message.
			return false;
		}
	}

	nodeList.push_back(pNode);
	return true;
}

void TaskManager::_UnregisterBehaviorNode(BehaviorNodeList& nodeList, BehaviorNode* pNode)
{
	ASSERT(pNode != NULL);
	if(NULL == pNode)
		return ;

	// Compare the address is OK. There doesn't exist the nodes with the same object id but different address.
	BehaviorNodeList::iterator it = std::find(nodeList.begin(), nodeList.end(), pNode);
	if(nodeList.end() != it) // exist
	{
		nodeList.remove(pNode);
		return ;
	}

	return ;
}

BehaviorNode* TaskManager::_GetBehaviorNodeById(const BehaviorNodeList& nodeList, const CString& objectId) const
{
	for(BehaviorNodeList::const_iterator it = nodeList.begin(); it != nodeList.end(); ++it)
	{
		BehaviorNode* pNode = *it;

		int iDiff = pNode->GetObjectId().CompareNoCase(objectId);
		if(0 == iDiff)
			return pNode;
	}

	return NULL;
}

void TaskManager::_DeleteBehaviorNodes(BehaviorNodeList& nodeList)
{
	BehaviorNodeList::iterator it = nodeList.begin();
	while(!nodeList.empty())
	{
		delete *it; // In its destructor, it will unregister itself from the list.
		it = nodeList.begin();
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

bool Action::IsParameterValid(const Parameter& para) const
{
	if(para.GetName().CompareNoCase(OBJECT_ID) == 0)
	{
		Action* pAction = TaskManager::Get()->GetActionById(para.GetEvaluatedValue());
		ASSERT(NULL == pAction);
		if(pAction != NULL) // Duplicated Id
			return false;
	}

	return true;
}
 
/************************************************************************
 The data format is:
 
 <Action>
	<Parameter> ...</Parameter>
	<Parameter>...</Parameter>
	<Parameter>...</Parameter>
	...
 </Action>
************************************************************************/
bool Action::XmlIn(XmlIOStream* pXmlIOStream)
{
	ASSERT(pXmlIOStream != NULL);
	return true;
}

bool Action::XmlOut(XmlIOStream* pXmlIOStream) const
{
	ASSERT(pXmlIOStream != NULL);	


	pXmlIOStream->BeginNode(_T("Action"));

	BehaviorNode::XmlOut(pXmlIOStream);

	pXmlIOStream->CloseNode();


	return true;
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

bool Condition::IsParameterValid(const Parameter& para) const
{
	if(para.GetName().CompareNoCase(OBJECT_ID) == 0)
	{
		Condition* pAction = TaskManager::Get()->GetConditionById(para.GetEvaluatedValue());
		ASSERT(NULL == pAction);
		if(pAction != NULL) // Duplicated Id
			return false;
	}

	return true;
}

/************************************************************************
 The data format is:
 
 <Condition>
	<Parameter> ...</Parameter>
	<Parameter>...</Parameter>
	<Parameter>...</Parameter>
	...
 </Condition>
************************************************************************/
bool Condition::XmlIn(XmlIOStream* pXmlIOStream)
{
	ASSERT(pXmlIOStream != NULL);
	return true;
}

bool Condition::XmlOut(XmlIOStream* pXmlIOStream) const
{
	ASSERT(pXmlIOStream != NULL);	


	pXmlIOStream->BeginNode(_T("Condition"));

	BehaviorNode::XmlOut(pXmlIOStream);

	pXmlIOStream->CloseNode();


	return true;
}
