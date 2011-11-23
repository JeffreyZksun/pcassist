#include "StdAfx.h"
#include "Actions.h"
#include "BrainUtil.h"
#include "ConstantsDefinition.h"
#include "BehaviorBodyFactory.h"
#include "TaskManager.h"
#include "BrainApplication.h"
#include "Logger.h"
#include "ExecutionContext.h"

BEHAVIORBODY_IMP(ComplexAction)
{
	// Condition
	Parameter condition;
	bool bExist = pContext->GetInputParameterTable()->GetParameter(EXECUTE_CONDITION, condition);
	ASSERT(bExist);
	if(!bExist)
		return false;

	Condition* pExeCondition = pContext->GetApplication()->GetTaskManager()->GetConditionById(condition.GetEvaluatedValue());
	ASSERT(pExeCondition != NULL);
	if(NULL == pExeCondition)
		return false;

	if(!pExeCondition->IsTrue()) // The condition isn't meet. Don't run return true.
		return true;

	// Main action, required.
	Parameter mainAction;
	bExist = pContext->GetInputParameterTable()->GetParameter(MAIN_ACTION, mainAction);
	ASSERT(bExist);
	if(!bExist)
		return false;

	Action* pMainAction = BrainApplication::GetWorkingBrain()->GetTaskManager()->GetActionById(mainAction.GetEvaluatedValue());
	ASSERT(pMainAction != NULL);
	if(NULL == pMainAction)
		return false;

	// Pre action, optional.
	Parameter preAction;
	bExist = pContext->GetInputParameterTable()->GetParameter(PRE_ACTION, preAction);
	if(bExist)
	{
		Action* pPreAction = pContext->GetApplication()->GetTaskManager()->GetActionById(preAction.GetEvaluatedValue());
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
		Action* pPostAction = pContext->GetApplication()->GetTaskManager()->GetActionById(postAction.GetEvaluatedValue());
		if(pPostAction != NULL)
			pPostAction->Execute();
	}

	return bRet;
}

BEHAVIORBODY_IMP(CreateFileAction)
{
    Parameter para;
    bool bExist = pContext->GetInputParameterTable()->GetParameter(FILE_NAME, para);
    ASSERT(bExist);

    if(bExist)
        return BrainUtil::CreateFile(para.GetEvaluatedValue());

    return false;
}

BEHAVIORBODY_IMP(DeleteFileAction)
{
    Parameter para;
    bool bExist = pContext->GetInputParameterTable()->GetParameter(FILE_NAME, para);
    ASSERT(bExist);

    if(bExist)
        return BrainUtil::DeleteFile(para.GetEvaluatedValue());

    return false;
}

BEHAVIORBODY_IMP(CopyFileAction)
{
    Parameter para1;
    bool bExist = pContext->GetInputParameterTable()->GetParameter(SRC_FILE_NAME, para1);
    ASSERT(bExist);
    if(!bExist)
        return false;

    Parameter para2;
    bExist = pContext->GetInputParameterTable()->GetParameter(DEST_FILE_NAME, para2);
    ASSERT(bExist);
    if(!bExist)
        return false;

    return BrainUtil::CopyFile(para1.GetEvaluatedValue(), para2.GetEvaluatedValue());
}

BEHAVIORBODY_IMP(CreateFolderAction)
{
    Parameter para;
    bool bExist = pContext->GetInputParameterTable()->GetParameter(FOLDER_NAME, para);
    ASSERT(bExist);

    if(bExist)
        return BrainUtil::CreateFolder(para.GetEvaluatedValue());

    return false;
}

BEHAVIORBODY_IMP(DeleteFolderAction)
{
    Parameter para;
    bool bExist = pContext->GetInputParameterTable()->GetParameter(FOLDER_NAME, para);
    ASSERT(bExist);

    if(bExist)
        return BrainUtil::DeleteFolder(para.GetEvaluatedValue());

    return false;
}

BEHAVIORBODY_IMP(CopyFolderAction)
{
    Parameter para1;
    bool bExist = pContext->GetInputParameterTable()->GetParameter(SRC_Folder_NAME, para1);
    ASSERT(bExist);
    if(!bExist)
        return false;

    Parameter para2;
    ASSERT(bExist);
    bExist = pContext->GetInputParameterTable()->GetParameter(DEST_Folder_NAME, para2);
    if(!bExist)
        return false;

    return BrainUtil::CopyFolder(para1.GetEvaluatedValue(), para2.GetEvaluatedValue());
}

BEHAVIORBODY_IMP(MakeDirectoryLinkAction)
{
    Parameter para1;
    bool bExist = pContext->GetInputParameterTable()->GetParameter(LINK_NAME, para1);
    ASSERT(bExist);
    if(!bExist)
        return false;

    Parameter para2;
    ASSERT(bExist);
    bExist = pContext->GetInputParameterTable()->GetParameter(LINK_TARGET, para2);
    if(!bExist)
        return false;

    return BrainUtil::MakeLink(para1.GetEvaluatedValue(), para2.GetEvaluatedValue());
}

BEHAVIORBODY_IMP(RunSystemCommandAction)
{
	Parameter para;
	bool bExist = pContext->GetInputParameterTable()->GetParameter(APPLICATION_NAME, para);
	ASSERT(bExist);
	if(!bExist)
		return false;

	CString applicationName = para.GetEvaluatedValue();

	bExist = pContext->GetInputParameterTable()->GetParameter(APPLICATION_PARAMETER, para);
	if(bExist)
	{
		CString applicationParameter = para.GetEvaluatedValue();

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
	ASSERT(bExist);
	if(!bExist)
		return false;

	CString applicationName = para.GetEvaluatedValue();

	bExist = pContext->GetInputParameterTable()->GetParameter(APPLICATION_PARAMETER, para);
	CString applicationParameter;
	if(bExist)
	{
		applicationParameter = para.GetEvaluatedValue();
	}

	bExist = pContext->GetInputParameterTable()->GetParameter(APPLICATION_SHOWWINDOW, para);
	bool bShowWindow = true;
	if(bExist)
	{
		CString strShowWindow = para.GetEvaluatedValue();
		if(strShowWindow.CompareNoCase(_T("false")) == 0)
			bShowWindow = false;
	}

	bExist = pContext->GetInputParameterTable()->GetParameter(WAIT_FOR_EXIT, para);
	bool bWaitForExit = true;
	if(bExist)
	{
		CString strWaitForExit = para.GetEvaluatedValue();
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
	ASSERT(bExist);
	if(!bExist)
		return true;

	Parameter para2;
	bExist = pContext->GetInputParameterTable()->GetParameter(EXPECTED_RESULT, para2);
	ASSERT(bExist);
	if(!bExist)
		return true;
	CString strExpectedRet = para2.GetEvaluatedValue();
	strExpectedRet.MakeLower();
	bool bExpectedResult = strExpectedRet == _T("true");

	// ToDo - Support time out.
	//Parameter para3;
	//bExist = pContext->GetInputParameterTable()->GetParameter(EXPECTED_RESULT, para3);

	Condition* pCondition = pContext->GetApplication()->GetTaskManager()->GetConditionById(para.GetEvaluatedValue());

	ASSERT(pCondition);
	bool bTimeOut = false;
	while(pCondition->IsTrue() != bExpectedResult)
	{
		// Sleep
		Sleep(1000);
	}


	return !bTimeOut;
}

