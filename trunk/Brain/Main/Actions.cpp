#include "StdAfx.h"
#include "Actions.h"
#include "BrainUtil.h"
#include "ConstantsDefinition.h"
#include "CloseLoopChecker.h"
#include "BehaviorBodyFactory.h"
#include "TaskManager.h"
#include "BrainApplication.h"
#include "Logger.h"
#include "ExecutionContext.h"

CloseLoopChecker sComplexActionCloseLoopChecker;

BEHAVIORBODY_IMP(ComplexAction)
{
	// Condition
	Parameter condition;
	bool bExist = pContext->GetInputParameterTable()->GetParameter(EXECUTE_CONDITION, condition);
	ASSERT(bExist);
	if(!bExist)
		return false;

	Condition* pExeCondition = BrainApplication::GetWorkingBrain()->GetTaskManager()->GetConditionById(condition.GetEvaluatedValue());
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

	// Detect dead loop caused by the close loop reference. Such as A<-->B
	if(!sComplexActionCloseLoopChecker.PushOngoingItem(pContext->GetBehaviorNode()->GetObjectId()))
	{
		// This variable is already in the evaluation stack. 
		// Close  loop reference is detected.
		// Return directly to avoid dead loop.
		ASSERT(!_T("Close loop reference is detected during evaluation."));

		return false; 
	}

	// Pre action, optional.
	Parameter preAction;
	bExist = pContext->GetInputParameterTable()->GetParameter(PRE_ACTION, preAction);
	if(bExist)
	{
		Action* pPreAction = BrainApplication::GetWorkingBrain()->GetTaskManager()->GetActionById(preAction.GetEvaluatedValue());
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
		Action* pPostAction = BrainApplication::GetWorkingBrain()->GetTaskManager()->GetActionById(postAction.GetEvaluatedValue());
		if(pPostAction != NULL)
			pPostAction->Execute();
	}

	sComplexActionCloseLoopChecker.Pop();

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

	return BrainUtil::RunSystemCommand(applicationName);
}

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

	// http://msdn.microsoft.com/en-us/library/ms682425%28v=vs.85%29.aspx
	// Create process
	//
	STARTUPINFO startupInfo;
	memset(&startupInfo, 0, sizeof(startupInfo));
	startupInfo.cb = sizeof(STARTUPINFO);
	startupInfo.dwFlags = STARTF_USESHOWWINDOW;

	bExist = pContext->GetInputParameterTable()->GetParameter(APPLICATION_SHOWWINDOW, para);
	bool bShowWindow = true;
	if(bExist)
	{
		CString strShowWindow;
		strShowWindow = para.GetEvaluatedValue();
		if(strShowWindow.CompareNoCase(_T("false")) == 0)
			bShowWindow = false;
	}
	startupInfo.wShowWindow = bShowWindow ? SW_NORMAL : SW_HIDE;

	PROCESS_INFORMATION processInformation;

	// We need the application name is the first parameter
	// When there is parameter, we need start the process with cmd line only.
	// We need to avoid the case below.

	//Test Running...
	//	AppName:  C:\CreateProcessBug\Debug\ParamTest.exe
	//	CmdLine:  Param1 Param2 Param3
	//ParamTest Output:
	//	Number of parameters: 3
	//	Parameter Info:
	//		Param #0: Param1
	//		Param #1: Param2
	//		Param #2: Param3

	CString cmdLine;
	BOOL ret = FALSE;
	if(applicationParameter.IsEmpty())
	{
		//Test Running...
		//	AppName:  C:\CreateProcessBug\Debug\ParamTest.exe
		//	CmdLine:  (null)
		//ParamTest Output:
		//	Number of parameters: 1
		//	Parameter Info:
		//		Param #0: C:\CreateProcessBug\Debug\ParamTest.exe
		ret = CreateProcess((LPCTSTR)applicationName, NULL, NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, &startupInfo, &processInformation);
	}
	else
	{
		//Test Running...
		//	AppName:  (null)
		//	CmdLine:  "C:\CreateProcessBug\Debug\ParamTest.exe" Param1 Param2 Param3
		//ParamTest Output:
		//	Number of parameters: 4
		//	Parameter Info:
		//		Param #0: C:\CreateProcessBug\Debug\ParamTest.exe
		//		Param #1: Param1
		//		Param #2: Param2
		//		Param #3: Param3

		cmdLine = applicationName + _T(" ") + applicationParameter;

		TCHAR tempCmdLine[MAX_PATH * 2];  //Needed since CreateProcessW may change the contents of CmdLine
		_tcscpy_s(tempCmdLine, MAX_PATH *2, (LPCTSTR)cmdLine);

		ret = CreateProcess(NULL, tempCmdLine, NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, &startupInfo, &processInformation);
	}

	if (!ret || !processInformation.hThread || !processInformation.hProcess)
	{
		if(applicationParameter.IsEmpty())
			BrainUtil::LogOutLastError(applicationName);
		else
			BrainUtil::LogOutLastError(cmdLine);

		return false;
	}

	WaitForSingleObject( processInformation.hProcess, INFINITE );
	CloseHandle( processInformation.hProcess );
	CloseHandle( processInformation.hThread );

	return true;
}

