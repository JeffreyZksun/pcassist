#include "StdAfx.h"
#include "TaskManager.h"
#include <algorithm>
#include <atltime.h> // CTime
#include "ConstantsDefinition.h"
#include "XmlIOStream.h"
#include "BehaviorBodyFactory.h"
#include "Logger.h"
#include "BrainApplication.h"
#include "ExecutionContext.h"
#include "IBehaviorBody.h"

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

	mTaskList.clear();
}

bool TaskManager::RegisterAction(Action* pAction)
{
	return _RegisterBehaviorNode(mRegisteredActions, pAction);
}

void TaskManager::UnregisterAction(Action* pAction)
{
    _UnregisterBehaviorNode(mRegisteredActions, pAction);

	//RemoveActionTask(pAction);
}

Action*	TaskManager::GetActionById(const CString& objectId) const
{
	BehaviorNode* pNode = _GetBehaviorNodeById(mRegisteredActions, objectId);

	Action* pAction = NULL;
	if(pNode != NULL)
		pAction = dynamic_cast<Action*>(pNode);

	return pAction;
}

Action* TaskManager::GetActionByIndex(size_t index) const
{
	if(index <0 || index >= GetActionCount())
		return NULL;

	BehaviorNode* pNode = NULL;
	size_t i = 0;
	for(BehaviorNodeList::const_iterator it = mRegisteredActions.begin(); it != mRegisteredActions.end(); ++it)
	{
		if(i == index)
			pNode = *it;
		i++;
	}

	Action* pAction = NULL;
	if(pNode != NULL)
		pAction = dynamic_cast<Action*>(pNode);

	return pAction;
}

size_t TaskManager::GetActionCount() const
{
	return mRegisteredActions.size();
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

	// The same action can be added more than once. Don't need the duplication check.
    mTaskList.push_back(pAction->GetObjectId().MakeLower());
}

void TaskManager::RemoveActionTask(Action* pAction)
{
	ASSERT(pAction != NULL);
	if(NULL == pAction)
		return;

	CString actionId = pAction->GetObjectId().MakeLower();
    ActionList::iterator it = std::find(mTaskList.begin(), mTaskList.end(), actionId);

    while(mTaskList.end() != it) // exist
	{
        mTaskList.remove(actionId);
		it = std::find(mTaskList.begin(), mTaskList.end(), actionId);
	}
}

bool TaskManager::RunTasks()
{
	// Log format.
	//	[==========] Task Begin. (##:##:##)// current time
	//	[----------]
	//	[ACTION    ]
	//	[   SUCCESS]
	//	[----------](## ms)
	//
	//	[----------]
	//	[ACTION    ]
	//	[   SUCCESS]
	//	[----------](## ms)
	//	
	//	[==========] Task Finish.(## ms total)

	CTime taskBeginTime = CTime::GetCurrentTime();

	//int hour = taskBeginTime.GetHour();
	//int minute = taskBeginTime.GetMinute();
	//int second = taskBeginTime.GetSecond();

	int succNum = 0;
	int failNum = 0;
	LogOut(_T("[==========]"), COLOR_GREEN); // 10 chars
	LogOut(_T(" Task Begin."));
	CString strStartTime = _T(" (12:14:34)"); 
	strStartTime.Format(_T(" (%d:%d:%d)"), taskBeginTime.GetHour(), taskBeginTime.GetMinute(), taskBeginTime.GetSecond());
	LogOut(strStartTime);
	LogOut(_T("\n")); 

	bool bRet = true;

    for (ActionList::iterator it = mTaskList.begin(); it != mTaskList.end(); ++it)
    {
		LogOut(_T("[----------]\n"), COLOR_GREEN); // 10 chars

		CTime actionBeginTime = CTime::GetCurrentTime();

		Action* pCurrentAction = GetActionById(*it);
		ASSERT(pCurrentAction != NULL);
		if(NULL != pCurrentAction)
		{
			bRet = pCurrentAction->Execute();
		}
		else
		{
			LogOut(_T("Error: The action ["), COLOR_RED); 
			LogOut(*it, COLOR_RED); 
			LogOut(_T("] isn't registered.\n"), COLOR_RED); 
			bRet = false;
		}

		CTimeSpan elapsedTime = CTime::GetCurrentTime() - actionBeginTime;

		if(bRet)
			succNum++;
		else
			failNum++;

		LogOut(_T("[----------]"), COLOR_GREEN); // 10 chars
		CString actionDuration = _T(" (10 s)"); 
		actionDuration.Format(_T(" (%d s)"), elapsedTime.GetTotalSeconds());
		LogOut(actionDuration);
		LogOut(_T("\n\n")); 

        // Check the BreakOnFail.
        if(pCurrentAction != NULL && !bRet)
        {
            Parameter para;
            bool bExit = pCurrentAction->GetParameterTable().GetParameter(BREAK_ON_FAIL, para);
            if(bExit)
            {
                if( para.GetEvaluatedValue().CompareNoCase(_T("true")) == 0)
                {
                    LogOut(_T("ERROR: Break the task due to the failed action ["), COLOR_RED); 
                    LogOut(*it, COLOR_RED); 
                    LogOut(_T("] \n\n"), COLOR_RED); 
                    break;
                }
            }
        }

    }

	bRet = (0 == failNum);

	LogOut(_T("[==========]"), COLOR_GREEN); // 10 chars
	LogOut(_T(" Task Finish.")); 
	// Task duration.

	CString taskDuration = _T(" (3620 s)");
	CTimeSpan elapsedTime = CTime::GetCurrentTime() - taskBeginTime;
	taskDuration.Format(_T(" (%d s)"), elapsedTime.GetTotalSeconds());
	LogOut(taskDuration);
	LogOut(_T("\n")); 

    // Total
    LogOut(_T("[ TOTAL    ]")); // 10 chars
    CString strNum;
    strNum.Format(_T(" %d actions\n"), mTaskList.size());
    LogOut(strNum);

    // Success
	LogOut(_T("[ SUCCESS  ]"), COLOR_GREEN); // 10 chars
	strNum.Format(_T(" %d actions\n"), succNum);
	LogOut(strNum);

    // Fail
	if(!bRet)
	{
		LogOut(_T("[  FAIL    ]"), COLOR_RED); // 10 chars
		strNum.Format(_T(" %d actions\n"), failNum);
		LogOut(strNum);
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

#define TaskListNode _T("TaskList")
#define ActionsNode _T("Actions")
#define ConditionsNode _T("Conditions")
#define ActionIdNode _T("ActionId")
#define ActionNode _T("Action")
#define ConditionNode _T("Condition")

bool TaskManager::XmlIn(XmlIOStream* pXmlIOStream)
{
	ASSERT(pXmlIOStream != NULL);

	// Actions
	{
		XmlIOStreamBeginNodeStack stack(pXmlIOStream, ActionsNode);
		if(stack.IsSuccess())
		{
			int index = 0;
			while(true)
			{		
				bool bHasItem = pXmlIOStream->ReadNode(ActionNode, index);
				if(!bHasItem)
					break;

				Action* pNewAction = new Action(); // The action is registered in its ctor
				pNewAction->XmlIn(pXmlIOStream);

				index++;

				pXmlIOStream->CloseNode();
			}
		}
	}
	
	// Conditions
	{
		XmlIOStreamBeginNodeStack stack(pXmlIOStream, ConditionsNode);
		if(stack.IsSuccess())
		{
			int index = 0;
			while(true)
			{		
				bool bHasItem = pXmlIOStream->ReadNode(ConditionNode, index);
				if(!bHasItem)
					break;

				Condition* pNewCondition = new Condition(); // The action is registered in its ctor
				pNewCondition->XmlIn(pXmlIOStream);

				index++;

				pXmlIOStream->CloseNode();
			}
		}
	}

	// TaskList 
	{
		XmlIOStreamBeginNodeStack stack(pXmlIOStream, TaskListNode);
		if(stack.IsSuccess())
		{
			int index = 0;
			while(true)
			{		
				bool bHasItem = pXmlIOStream->ReadNode(ActionIdNode, index);
				if(!bHasItem)
					break;

				CString actionObjectId;
				pXmlIOStream->ReadNodeText(actionObjectId);
				mTaskList.push_back(actionObjectId);

				index++;

				pXmlIOStream->CloseNode();
			}
		}
	}

	return true;
}

bool TaskManager::XmlOut(XmlIOStream* pXmlIOStream) const
{
	ASSERT(pXmlIOStream != NULL);

	// TaskList
	{
		XmlIOStreamBeginNodeStack stack(pXmlIOStream, TaskListNode);
		if(stack.IsSuccess())
		{
			for (ActionList::const_iterator it = mTaskList.begin(); it != mTaskList.end(); ++it)
			{
				XmlIOStreamBeginNodeStack stack2(pXmlIOStream, ActionIdNode);
				if(stack2.IsSuccess())
					pXmlIOStream->WriteNodeText(*it);
			}
		}
	}

	// Actions
	{
		XmlIOStreamBeginNodeStack stack(pXmlIOStream, ActionsNode);
		if(stack.IsSuccess())
		{
			for (BehaviorNodeList::const_iterator it = mRegisteredActions.begin(); it != mRegisteredActions.end(); ++it)
			{
				ASSERT(*it != NULL);
				XmlIOStreamBeginNodeStack stack2(pXmlIOStream, ActionNode);
				if(stack2.IsSuccess())
					(*it)->XmlOut(pXmlIOStream);
			}
		}
	}

	//Conditions
	{
		XmlIOStreamBeginNodeStack stack(pXmlIOStream, ConditionsNode);
		if(stack.IsSuccess())
		{
			for (BehaviorNodeList::const_iterator it = mRegisteredContions.begin(); it != mRegisteredContions.end(); ++it)
			{
				ASSERT(*it != NULL);
				XmlIOStreamBeginNodeStack stack2(pXmlIOStream, ConditionNode);
				if(stack2.IsSuccess())
					(*it)->XmlOut(pXmlIOStream);
			}
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
		//nodeList.pop_front(); // Don't need the pop operation.
		it = nodeList.begin();
	}
}
//////////////////////////////////////////////////////////////////////////
// BehaviorNode
//////////////////////////////////////////////////////////////////////////

BehaviorNode::BehaviorNode() : mParameterTable()
	, mpBrainApplication(BrainApplication::GetWorkingBrain())
	, mbIsExecuting(false)
{
	int address = (int)this;
	CString objectId;
	objectId.Format(_T("%d"), address);
	mParameterTable.AddParameter(Parameter(OBJECT_ID, objectId));	// Used for query the object
}

BehaviorNode::BehaviorNode(const CString& objetType) : mParameterTable()
	, mpBrainApplication(BrainApplication::GetWorkingBrain())
	, mbIsExecuting(false)
{
	int address = (int)this;
	CString objectId;
	objectId.Format(_T("%d"), address);
	mParameterTable.AddParameter(Parameter(OBJECT_ID, objectId));	// Used for query the object
	mParameterTable.AddParameter(Parameter(OBJECT_TYPE, objetType));// Used for select the behavior function.
}

BehaviorNode::~BehaviorNode()
{
	mpBrainApplication = NULL;
}

CString BehaviorNode::GetObjectId() const
{
	Parameter para;
	bool bExist = mParameterTable.GetParameter(OBJECT_ID, para);
	ASSERT(bExist);
	if(!bExist)
		return _T("");

	return para.GetEvaluatedValue();
}

CString BehaviorNode::GetObjectType() const
{
	Parameter para;
	bool bExist = mParameterTable.GetParameter(OBJECT_TYPE, para);
	ASSERT(bExist);
	if(!bExist)
		return _T("");

	return para.GetEvaluatedValue();
}

ParameterTable& BehaviorNode::GetParameterTable()
{
	return mParameterTable;
}

bool BehaviorNode::XmlIn(XmlIOStream* pXmlIOStream)
{
	return mParameterTable.XmlIn(pXmlIOStream);
}

bool BehaviorNode::XmlOut(XmlIOStream* pXmlIOStream) const
{
	return mParameterTable.XmlOut(pXmlIOStream);
}

BrainApplication* BehaviorNode::GetApplication() const
{
	return mpBrainApplication;
}

bool BehaviorNode::ExecuteBehavior()
{
	// Log message format.
	//	[ACTION   ][OBJECT_TYPE] - OBJECT_ID
	//			para name=para value
	//			...
	//	[   SUCCESS]
	//	[      FAIL]

	//	[CONDITION ][OBJECT_TYPE] - OBJECT_ID
	//			para name=para value
	//			...
	//	[      TRUE]
	//	[     FALSE]

	if(true == mbIsExecuting)
	{
		ASSERT(!_T("Error: Behavior execution loop is detected"));
		LogOut(_T("Error: Behavior execution loop is detected=> "), COLOR_RED);
		LogOut(GetObjectId(), COLOR_RED);
		LogOut(_T("\n"), COLOR_RED);
		return false;
	}

	mbIsExecuting = true;
	LogOut(_T(" [")); LogOut(GetObjectType()); LogOut(_T("] - ")); LogOut(GetObjectId()); LogOut(_T("\n"));
	if(Logger::Get()->DoesOuputParameter())
	{
		for (unsigned int i = 0; i < mParameterTable.GetParameterLength(); i++)
		{
			Parameter para;
			mParameterTable.GetParameter(i, para);

			if(para.GetName().CompareNoCase(OBJECT_ID) == 0)
				continue;

			if(para.GetName().CompareNoCase(OBJECT_TYPE) == 0)
				continue;

			// 12 + 1 empty chars
			LogOut(_T("             ")); LogOut(para.GetName()); LogOut(_T("=")); LogOut(para.GetEvaluatedValue()); LogOut(_T("\n"));
		}
	}

	bool bSucc = true;

	IBehaviorBody *pBody = GetApplication()->GetBehaviorBodyFactory()->GetBehaviorBody(GetObjectType());
	if(NULL != pBody)
	{
		ExecutionContext context(this, &mParameterTable);

		bSucc = pBody->Execute(&context);
	}
	else
	{
		// 12 + 1 empty chars
		LogOut(_T("             "));LogOut(_T("Unknown object type.\n"));
		bSucc = false;
	}

	mbIsExecuting = false;

	return bSucc;
}

//////////////////////////////////////////////////////////////////////////
// Action
//////////////////////////////////////////////////////////////////////////
Action::Action()
{
	TaskManager* pTaskMgr = GetApplication()->GetTaskManager();
	pTaskMgr->RegisterAction(this);
}

Action::Action(const CString& objetType)
	: BehaviorNode(objetType)
{
    TaskManager* pTaskMgr = GetApplication()->GetTaskManager();
    pTaskMgr->RegisterAction(this);
}

Action::~Action(void)
{
    TaskManager* pTaskMgr = GetApplication()->GetTaskManager();
    pTaskMgr->UnregisterAction(this);
}

bool Action::IsParameterValid(const Parameter& para) const
{
	if(para.GetName().CompareNoCase(OBJECT_ID) == 0)
	{
		Action* pAction = GetApplication()->GetTaskManager()->GetActionById(para.GetEvaluatedValue());
		ASSERT(NULL == pAction);
		if(pAction != NULL) // Duplicated Id
			return false;
	}

	return true;
}

bool Action::Execute()
{
	// 10 chars in the brackets
	LogOut(_T("[ACTION    ]"), COLOR_GREEN);
	bool bSucc = ExecuteBehavior();

	if(bSucc)
		LogOut(_T("[   SUCCESS]\n"), COLOR_GREEN);
	else
		LogOut(_T("[      FAIL]\n"), COLOR_RED);

	//LogOut(_T("\n"));

	return bSucc;
}

//////////////////////////////////////////////////////////////////////////
// Condition
//////////////////////////////////////////////////////////////////////////

Condition::Condition()
{
	TaskManager* pTaskMgr = GetApplication()->GetTaskManager();
	pTaskMgr->RegisterCondition(this);
}

Condition::Condition(const CString& objetType)
	: BehaviorNode(objetType)
{
    TaskManager* pTaskMgr = GetApplication()->GetTaskManager();
    pTaskMgr->RegisterCondition(this);
}

Condition::~Condition(void)
{
    TaskManager* pTaskMgr = GetApplication()->GetTaskManager();
    pTaskMgr->UnregisterCondition(this);
}

bool Condition::IsParameterValid(const Parameter& para) const
{
	if(para.GetName().CompareNoCase(OBJECT_ID) == 0)
	{
		Condition* pAction = GetApplication()->GetTaskManager()->GetConditionById(para.GetEvaluatedValue());
		ASSERT(NULL == pAction);
		if(pAction != NULL) // Duplicated Id
			return false;
	}

	return true;
}

bool Condition::IsTrue()
{
	// 10 chars in the brackets
	LogOut(_T("[CONDITION ]"), COLOR_GREEN);
	bool bSucc = ExecuteBehavior();

	if(bSucc)
		LogOut(_T("[      TRUE]\n"), COLOR_GREEN);
	else
		LogOut(_T("[     FALSE]\n"), COLOR_GREEN);

	//LogOut(_T("\n"));

	return bSucc;
}
