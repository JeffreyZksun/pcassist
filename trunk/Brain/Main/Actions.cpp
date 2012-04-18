#include "StdAfx.h"
#include "Actions.h"
#include "BrainUtil.h"
#include "ConstantsDefinition.h"
#include "BehaviorBodyFactory.h"
#include "BehaviorManager.h"
#include "TaskSystem.h"
#include "Logger.h"
#include "ExecutionContext.h"

BEHAVIORBODY_IMP(ComplexAction)
{
	// Condition
	Parameter condition;
	bool bExist = pContext->GetInputParameterTable()->GetParameter(EXECUTE_CONDITION, condition);
	DATA_ASSERT(bExist);
	if(!bExist)
		return false;

	ConditionPtr pExeCondition = pContext->GetTaskSystem()->GetBehaviorManager()->GetConditionById(condition.GetEvaluatedValue(pContext->GetTaskSystem()->GetVariableManager()));
	DATA_ASSERT(pExeCondition != NULL);
	if(NULL == pExeCondition)
		return false;

	if(!pExeCondition->IsTrue()) // The condition isn't meet. Don't run return true.
		return true;

	// Main action, required.
	Parameter mainAction;
	bExist = pContext->GetInputParameterTable()->GetParameter(MAIN_ACTION, mainAction);
	DATA_ASSERT(bExist);
	if(!bExist)
		return false;

	ActionPtr pMainAction = pContext->GetTaskSystem()->GetBehaviorManager()->GetActionById(mainAction.GetEvaluatedValue(pContext->GetTaskSystem()->GetVariableManager()));
	DATA_ASSERT(pMainAction != NULL);
	if(NULL == pMainAction)
		return false;

	// Pre action, optional.
	Parameter preAction;
	bExist = pContext->GetInputParameterTable()->GetParameter(PRE_ACTION, preAction);
	if(bExist)
	{
		ActionPtr pPreAction = pContext->GetTaskSystem()->GetBehaviorManager()->GetActionById(preAction.GetEvaluatedValue(pContext->GetTaskSystem()->GetVariableManager()));
		if(pPreAction != NULL)
			pPreAction->Execute();
	}

	// Main action
	bool bRet = pMainAction->Execute();

	// Post action, optional.
	Parameter postAction;
	bExist = pContext->GetInputParameterTable()->GetParameter(POST_ACTION, postAction);
	if(bExist)
	{
		ActionPtr pPostAction = pContext->GetTaskSystem()->GetBehaviorManager()->GetActionById(postAction.GetEvaluatedValue(pContext->GetTaskSystem()->GetVariableManager()));
		if(pPostAction != NULL)
			pPostAction->Execute();
	}

	return bRet;
}

BEHAVIORBODY_IMP(CreateFileAction)
{
    Parameter para;
    bool bExist = pContext->GetInputParameterTable()->GetParameter(FILE_NAME, para);
    DATA_ASSERT(bExist);

    if(bExist)
        return BrainUtil::CreateFile(para.GetEvaluatedValue(pContext->GetTaskSystem()->GetVariableManager()));

    return false;
}

BEHAVIORBODY_IMP(DeleteFileAction)
{
    Parameter para;
    bool bExist = pContext->GetInputParameterTable()->GetParameter(FILE_NAME, para);
    DATA_ASSERT(bExist);

    if(bExist)
        return BrainUtil::DeleteFile(para.GetEvaluatedValue(pContext->GetTaskSystem()->GetVariableManager()));

    return false;
}

BEHAVIORBODY_IMP(CopyFileAction)
{
    Parameter para1;
    bool bExist = pContext->GetInputParameterTable()->GetParameter(SRC_FILE_NAME, para1);
    DATA_ASSERT(bExist);
    if(!bExist)
        return false;

    Parameter para2;
    bExist = pContext->GetInputParameterTable()->GetParameter(DEST_FILE_NAME, para2);
    DATA_ASSERT(bExist);
    if(!bExist)
        return false;

    return BrainUtil::CopyFile(para1.GetEvaluatedValue(pContext->GetTaskSystem()->GetVariableManager()), para2.GetEvaluatedValue(pContext->GetTaskSystem()->GetVariableManager()));
}

BEHAVIORBODY_IMP(CreateFolderAction)
{
    Parameter para;
    bool bExist = pContext->GetInputParameterTable()->GetParameter(FOLDER_NAME, para);
    DATA_ASSERT(bExist);

    if(bExist)
        return BrainUtil::CreateFolder(para.GetEvaluatedValue(pContext->GetTaskSystem()->GetVariableManager()));

    return false;
}

BEHAVIORBODY_IMP(DeleteFolderAction)
{
    Parameter para;
    bool bExist = pContext->GetInputParameterTable()->GetParameter(FOLDER_NAME, para);
    DATA_ASSERT(bExist);

    if(bExist)
        return BrainUtil::DeleteFolder(para.GetEvaluatedValue(pContext->GetTaskSystem()->GetVariableManager()));

    return false;
}

BEHAVIORBODY_IMP(CopyFolderAction)
{
    Parameter para1;
    bool bExist = pContext->GetInputParameterTable()->GetParameter(SRC_Folder_NAME, para1);
    DATA_ASSERT(bExist);
    if(!bExist)
        return false;

    Parameter para2;
    DATA_ASSERT(bExist);
    bExist = pContext->GetInputParameterTable()->GetParameter(DEST_Folder_NAME, para2);
    if(!bExist)
        return false;

    return BrainUtil::CopyFolder(para1.GetEvaluatedValue(pContext->GetTaskSystem()->GetVariableManager()), para2.GetEvaluatedValue(pContext->GetTaskSystem()->GetVariableManager()));
}

BEHAVIORBODY_IMP(MakeDirectoryLinkAction)
{
    Parameter para1;
    bool bExist = pContext->GetInputParameterTable()->GetParameter(LINK_NAME, para1);
    DATA_ASSERT(bExist);
    if(!bExist)
        return false;

    Parameter para2;
    DATA_ASSERT(bExist);
    bExist = pContext->GetInputParameterTable()->GetParameter(LINK_TARGET, para2);
    if(!bExist)
        return false;

    return BrainUtil::MakeLink(para1.GetEvaluatedValue(pContext->GetTaskSystem()->GetVariableManager()), para2.GetEvaluatedValue(pContext->GetTaskSystem()->GetVariableManager()));
}

BEHAVIORBODY_IMP(RunSystemCommandAction)
{
	Parameter para;
	bool bExist = pContext->GetInputParameterTable()->GetParameter(APPLICATION_NAME, para);
	DATA_ASSERT(bExist);
	if(!bExist)
		return false;

	CString applicationName = para.GetEvaluatedValue(pContext->GetTaskSystem()->GetVariableManager());

	bExist = pContext->GetInputParameterTable()->GetParameter(APPLICATION_PARAMETER, para);
	if(bExist)
	{
		CString applicationParameter = para.GetEvaluatedValue(pContext->GetTaskSystem()->GetVariableManager());

		applicationName = applicationName + _T(" ") + applicationParameter;
	}

	bool bSucc =  BrainUtil::RunSystemCommand(applicationName);

	if(!bSucc)
		BrainUtil::LogOutLastError(applicationName);

	return bSucc;
}

// Refer to http://msdn.microsoft.com/en-us/library/ms682499%28VS.85%29.aspx
// For the stream indirection.
BEHAVIORBODY_IMP(RunProcessAction)
{
	Parameter para;
	bool bExist = pContext->GetInputParameterTable()->GetParameter(APPLICATION_NAME, para);
	DATA_ASSERT(bExist);
	if(!bExist)
		return false;

	CString applicationName = para.GetEvaluatedValue(pContext->GetTaskSystem()->GetVariableManager());

	bExist = pContext->GetInputParameterTable()->GetParameter(APPLICATION_PARAMETER, para);
	CString applicationParameter;
	if(bExist)
	{
		applicationParameter = para.GetEvaluatedValue(pContext->GetTaskSystem()->GetVariableManager());
	}

	bExist = pContext->GetInputParameterTable()->GetParameter(APPLICATION_SHOWWINDOW, para);
	bool bShowWindow = true;
	if(bExist)
	{
		CString strShowWindow = para.GetEvaluatedValue(pContext->GetTaskSystem()->GetVariableManager());
		if(strShowWindow.CompareNoCase(_T("false")) == 0)
			bShowWindow = false;
	}

	bExist = pContext->GetInputParameterTable()->GetParameter(WAIT_FOR_EXIT, para);
	bool bWaitForExit = true;
	if(bExist)
	{
		CString strWaitForExit = para.GetEvaluatedValue(pContext->GetTaskSystem()->GetVariableManager());
		if(strWaitForExit.CompareNoCase(_T("false")) == 0)
			bWaitForExit = false;
	}

    unsigned long ret = BrainUtil::RunProcess(applicationName, applicationParameter, bShowWindow, bWaitForExit);

	if (ret != 0)
	{
		BrainUtil::LogOutLastError(applicationName + _T(" ") + applicationParameter);

		return false;
	}

	return true;
}

BEHAVIORBODY_IMP(ConditionBlockAction)
{
	Parameter para;
	bool bExist = pContext->GetInputParameterTable()->GetParameter(CONDITION_ID, para);
	DATA_ASSERT(bExist);
	if(!bExist)
		return true;

	Parameter para2;
	bExist = pContext->GetInputParameterTable()->GetParameter(EXPECTED_RESULT, para2);
	DATA_ASSERT(bExist);
	if(!bExist)
		return true;
	CString strExpectedRet = para2.GetEvaluatedValue(pContext->GetTaskSystem()->GetVariableManager());
	strExpectedRet.MakeLower();
	bool bExpectedResult = strExpectedRet == _T("true");

	// ToDo - Support time out.
	//Parameter para3;
	//bExist = pContext->GetInputParameterTable()->GetParameter(EXPECTED_RESULT, para3);

	ConditionPtr pCondition = pContext->GetTaskSystem()->GetBehaviorManager()->GetConditionById(para.GetEvaluatedValue(pContext->GetTaskSystem()->GetVariableManager()));

	DATA_ASSERT(pCondition);
	bool bTimeOut = false;
	while(pCondition->IsTrue() != bExpectedResult)
	{
		// Sleep
		Sleep(1000);
	}


	return !bTimeOut;
}

// It references a action id list. 
// During execution it executes the referenced action one by one. 
// Return true if all the actions are success, otherwise return false.
//    The syntax for condition list parameter is like
//
//    <Parameter>
//      <Name>IdList</Name>
//      <value>
//          {1.1 Action 1}
//          {1.2 Action 2}
//          {1.3 Action 3}
//          {1.4 Action 4}
//      </value>
//    </Parameter>
BEHAVIORBODY_IMP(TaskListAction)
{
    Parameter para;
    bool bExist = pContext->GetInputParameterTable()->GetParameter(ID_LIST, para);
    DATA_ASSERT(bExist);
    if(!bExist)
        return true;

    CString strGroup = para.GetEvaluatedValue(pContext->GetTaskSystem()->GetVariableManager());

    std::vector<CString> actionIds;

    BrainUtil::ExtractSubItems(strGroup, actionIds);

    int succNum = 0;
    int failNum = 0;

    bool bRet = false;

    for(std::vector<CString>::const_iterator it = actionIds.begin(); it != actionIds.end(); it++)
    {
        ActionPtr pCurrentAction = pContext->GetTaskSystem()->GetBehaviorManager()->GetActionById(*it);
        DATA_ASSERT(pCurrentAction != NULL);
        if(NULL != pCurrentAction)
        {
            bRet = pCurrentAction->Execute();
        }
        else
        {
            LogOut(_T("Error: The action ["), COLOR_RED); 
			Ts::StringUtil util;
			LogOut(util.convert_to_wstring(*it), COLOR_RED); 
            LogOut(_T("] isn't registered.\n"), COLOR_RED); 
            bRet = false;
        }

        if(bRet)
            succNum++;
        else
            failNum++;
    }

    return (0 == failNum);
}

//Check all the conditions in the list. Return true if all the conditions are true. Otherwise return false.
//
//    This action can be used as sanity check.
//    The syntax for condition list parameter is like
//
//    <Parameter>
//      <Name>IdList</Name>
//      <value>
//          {1.1 Condition 1}
//          {1.2 Condition 2}
//          {1.3 Condition 3}
//          {1.4 Condition 4}
//      </value>
//    </Parameter>
BEHAVIORBODY_IMP(ConditionListCheckAction)
{
    Parameter para;
    bool bExist = pContext->GetInputParameterTable()->GetParameter(ID_LIST, para);
    DATA_ASSERT(bExist);
    if(!bExist)
        return true;

    CString strGroup = para.GetEvaluatedValue(pContext->GetTaskSystem()->GetVariableManager());

    std::vector<CString> actionIds;

    BrainUtil::ExtractSubItems(strGroup, actionIds);

    int trueNum = 0;
    int falseNum = 0;

    bool bRet = false;

    for(std::vector<CString>::const_iterator it = actionIds.begin(); it != actionIds.end(); it++)
    {
        ConditionPtr pCurrentCondition = pContext->GetTaskSystem()->GetBehaviorManager()->GetConditionById(*it);
        DATA_ASSERT(pCurrentCondition != NULL);
        if(NULL != pCurrentCondition)
        {
            bRet = pCurrentCondition->IsTrue();
        }
        else
        {
            LogOut(_T("Error: The Condition ["), COLOR_RED); 
			Ts::StringUtil util;
            LogOut(util.convert_to_wstring(*it), COLOR_RED); 
            LogOut(_T("] isn't registered.\n"), COLOR_RED); 
            bRet = false;
        }

        if(bRet)
            trueNum++;
        else
            falseNum++;
    }

    return (0 == falseNum);
}

// Do nothing just return true. For the test purpose.
BEHAVIORBODY_IMP(EmptyAction)
{
	return true;
}
