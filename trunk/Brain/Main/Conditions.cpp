#include "StdAfx.h"
#include "Conditions.h"
#include "BrainUtil.h"
#include "ConstantsDefinition.h"
#include "CloseLoopChecker.h"
#include "BehaviorBodyFactory.h"
#include "TaskManager.h"
#include "RegistryKey.h"
#include "BrainApplication.h"
#include "ExecutionContext.h"

CloseLoopChecker sComplexConditionCloseLoopChecker;

//////////////////////////////////////////////////////////////////////////
// ComplexCondition
//////////////////////////////////////////////////////////////////////////

//BehaviorFunctionHelper gComplexCondition(_T("ComplexCondition"), ComplexConditionFunction);
//bool ComplexConditionFunction(BehaviorNode* pSelf)
BEHAVIORBODY_IMP(ComplexCondition)
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

	Condition* pFstCondition = BrainApplication::GetWorkingBrain()->GetTaskManager()->GetConditionById(firstCondition.GetEvaluatedValue());
	ASSERT(pFstCondition != NULL);
	if(NULL == pFstCondition)
		return false;

	// Detect dead loop caused by the close loop reference. Such as A<-->B
	if(!sComplexConditionCloseLoopChecker.PushOngoingItem(pContext->GetBehaviorNode()->GetObjectId()))
	{
		// This variable is already in the evaluation stack. 
		// Close  loop reference is detected.
		// Return directly to avoid dead loop.
		ASSERT(!_T("Close loop reference is detected during evaluation."));

		return false;
	}

	bool bRet = false;
	if(oper.GetEvaluatedValue().CompareNoCase(_T("Not")) == 0)
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
			Condition* pSndCondition = BrainApplication::GetWorkingBrain()->GetTaskManager()->GetConditionById(sndCondition.GetEvaluatedValue());
			ASSERT(pSndCondition != NULL);
			if(pSndCondition != NULL)
			{
				if(oper.GetEvaluatedValue().CompareNoCase(_T("AND")) == 0)
				{
					bRet =  pFstCondition->IsTrue() && pSndCondition->IsTrue();
				}
				else if(oper.GetEvaluatedValue().CompareNoCase(_T("OR")) == 0)
				{
					bRet =  pFstCondition->IsTrue() || pSndCondition->IsTrue();
				}
			}
		}
	}

	sComplexConditionCloseLoopChecker.Pop();

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
        return BrainUtil::DoesFileorFolderExist(para.GetEvaluatedValue());
    
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
        return BrainUtil::DoesFileorFolderExist(para.GetEvaluatedValue());

    return false;
}

BEHAVIORBODY_IMP(RegisterKeyExistsCondition)
{
	Parameter para;
	bool bExist = pContext->GetInputParameterTable()->GetParameter(ROOT_KEY, para);
	ASSERT(bExist);
	if(!bExist)
		return false;
	CString rootKey = para.GetEvaluatedValue();

	bExist = pContext->GetInputParameterTable()->GetParameter(SUB_KEY, para);
	ASSERT(bExist);
	if(!bExist)
		return false;

	CString subKeyName = para.GetEvaluatedValue();

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

	RegistryKey subKey;
	BOOL bRet = subKey.OpenEx(hRootKey, (LPCTSTR)subKeyName);

	return TRUE == bRet;
}

