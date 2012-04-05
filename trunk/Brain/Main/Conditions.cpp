#include "StdAfx.h"
#include "Conditions.h"
#include "BrainUtil.h"
#include "ConstantsDefinition.h"
#include "BehaviorBodyFactory.h"
#include "TaskManager.h"
#include "RegistryKey.h"
#include "BrainApplication.h"
#include "ExecutionContext.h"

//////////////////////////////////////////////////////////////////////////
// ComplexCondition
//////////////////////////////////////////////////////////////////////////


BEHAVIORBODY_IMP(CompositeCondition)
{
	Parameter oper;
	bool bExist = pContext->GetInputParameterTable()->GetParameter(BOOL_OPERATOR, oper);
	ASSERT(bExist);
	if(!bExist)
		return false;

	Parameter firstCondition;
	bExist = pContext->GetInputParameterTable()->GetParameter(FIRST_CONDITION, firstCondition);
	ASSERT(bExist);
	if(!bExist)
		return false;

	Condition* pFstCondition = pContext->GetApplication()->GetTaskManager()->GetConditionById(firstCondition.GetEvaluatedValue(pContext->GetApplication()->GetVariableManager()));
	ASSERT(pFstCondition != NULL);
	if(NULL == pFstCondition)
		return false;

	bool bRet = false;
	if(oper.GetEvaluatedValue(pContext->GetApplication()->GetVariableManager()).CompareNoCase(_T("Not")) == 0)
	{
		bRet = !pFstCondition->IsTrue();
	}
	else 
	{
		Parameter sndCondition;
		bExist = pContext->GetInputParameterTable()->GetParameter(SECOND_CONDITION, sndCondition);
		ASSERT(bExist);
		if(bExist)
		{
			Condition* pSndCondition = BrainApplication::GetWorkingBrain()->GetTaskManager()->GetConditionById(sndCondition.GetEvaluatedValue(pContext->GetApplication()->GetVariableManager()));
			ASSERT(pSndCondition != NULL);
			if(pSndCondition != NULL)
			{
				if(oper.GetEvaluatedValue(pContext->GetApplication()->GetVariableManager()).CompareNoCase(_T("AND")) == 0)
				{
					bRet =  pFstCondition->IsTrue() && pSndCondition->IsTrue();
				}
				else if(oper.GetEvaluatedValue(pContext->GetApplication()->GetVariableManager()).CompareNoCase(_T("OR")) == 0)
				{
					bRet =  pFstCondition->IsTrue() || pSndCondition->IsTrue();
				}
			}
		}
	}

	return bRet;
}

//////////////////////////////////////////////////////////////////////////
// FileExistsCondition
//////////////////////////////////////////////////////////////////////////

BEHAVIORBODY_IMP(FileExistsCondition)
{
    Parameter para;
    bool bExist = pContext->GetInputParameterTable()->GetParameter(FILE_NAME, para);
    ASSERT(bExist);

    if(bExist)
        return BrainUtil::DoesFileorFolderExist(para.GetEvaluatedValue(pContext->GetApplication()->GetVariableManager()));
    
    return false;
}

//////////////////////////////////////////////////////////////////////////
// FolderExistsCondition
//////////////////////////////////////////////////////////////////////////


BEHAVIORBODY_IMP(FolderExistsCondition)
{
    Parameter para;
    bool bExist = pContext->GetInputParameterTable()->GetParameter(FOLDER_NAME, para);
    ASSERT(bExist);

    if(bExist)
        return BrainUtil::DoesFileorFolderExist(para.GetEvaluatedValue(pContext->GetApplication()->GetVariableManager()));

    return false;
}

BEHAVIORBODY_IMP(RegisterKeyExistsCondition)
{
	Parameter para;
	bool bExist = pContext->GetInputParameterTable()->GetParameter(ROOT_KEY, para);
	ASSERT(bExist);
	if(!bExist)
		return false;
	CString rootKey = para.GetEvaluatedValue(pContext->GetApplication()->GetVariableManager());

	bExist = pContext->GetInputParameterTable()->GetParameter(SUB_KEY, para);
	ASSERT(bExist);
	if(!bExist)
		return false;

	CString subKeyName = para.GetEvaluatedValue(pContext->GetApplication()->GetVariableManager());

	rootKey.MakeLower();
	HKEY hRootKey = NULL;

	if(rootKey.Find(_T("root")) != -1)
	{
		hRootKey = HKEY_CLASSES_ROOT;
	}
	else if(rootKey.Find(_T("current")) != -1)
	{
		hRootKey = HKEY_CURRENT_USER;
	}
	else if(rootKey.Find(_T("machine")) != -1)
	{
		hRootKey = HKEY_LOCAL_MACHINE;
	}
	else if(rootKey.Find(_T("users")) != -1)
	{
		hRootKey = HKEY_USERS;
	}
	else if(rootKey.Find(_T("config")) != -1)
	{
		hRootKey = HKEY_CURRENT_CONFIG;
	}

	if(NULL == hRootKey)
	{
		return false;
	}

    // On a Windows 64-bit system the Registry is actually divided into two parts. 
    // One section is used by 64-bit processes, and one part by 32-bit processes.
    //
    // For example, if a 32-bit application programatically writes to what it believes is 
    // HKLM\SOFTWARE\Company\Application, it's actually redirected by the WoW64-layer to 
    // HKLM\SOFTWARE\Wow6432Node\Company\Application.
    //
    // Use the flag KEY_WOW64_64KEY can indicate the correct path.
    // 
    // See the discussion regarding this below
    // http://stackoverflow.com/questions/252297/why-is-regopenkeyex-returning-error-code-2-on-vista-64bit
	RegistryKey subKey;
	BOOL bRet = subKey.OpenEx(hRootKey, (LPCTSTR)subKeyName, KEY_READ|KEY_WOW64_64KEY);

	return TRUE == bRet;
}

BEHAVIORBODY_IMP(ProcessRunningCondition)
{
	Parameter para;
	bool bExist = pContext->GetInputParameterTable()->GetParameter(PROCESS_NAME, para);
	ASSERT(bExist);
	if(!bExist)
		return false;
	CString strPorcessName = para.GetEvaluatedValue(pContext->GetApplication()->GetVariableManager());
	strPorcessName.Replace(_T('/'), _T('\\'));

	bool bCompareNameOnly = true;

	if(strPorcessName.Find(_T('\\')) != -1)
		bCompareNameOnly = false; // Include back slash meaning this is a full path name.

	bool bRet = BrainUtil::IsProcessRunning(strPorcessName, bCompareNameOnly);

	return bRet;
}

// It executes an action. And check if the result is equal to the expected result. If equal, the condition is true. 
BEHAVIORBODY_IMP(ActionResultCondition)
{
    Parameter para;
    bool bExist = pContext->GetInputParameterTable()->GetParameter(ACTION_ID, para);
    ASSERT(bExist);
    if(!bExist)
        return false;
    CString strActionId = para.GetEvaluatedValue(pContext->GetApplication()->GetVariableManager());
  
    Action* pAction = pContext->GetApplication()->GetTaskManager()->GetActionById(strActionId);
    ASSERT(pAction != NULL);
    if(NULL == pAction)
        return false;

    bool bRet = pAction->Execute();

    return bRet;
}


