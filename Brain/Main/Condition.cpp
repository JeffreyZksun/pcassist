#include "StdAfx.h"
#include "Condition.h"
#include "BrainUtil.h"
#include "ConstantsDefinition.h"
#include "CloseLoopChecker.h"

CloseLoopChecker sComplexConditionCloseLoopChecker;

//////////////////////////////////////////////////////////////////////////
// ComplexCondition
//////////////////////////////////////////////////////////////////////////

BEHAVIOR_CLASS_IMP(ComplexCondition, Condition)

bool ComplexCondition::IsTrue()
{
	Parameter oper;
	bool bExist = GetParameter(BOOL_OPERATOR, oper);
	ASSERT(bExist);
	if(!bExist)
		return false;

	Parameter firstCondition;
	bExist = GetParameter(FIRST_CONDITION, firstCondition);
	ASSERT(bExist);
	if(!bExist)
		return false;

	Condition* pFstCondition = TaskManager::Get()->GetConditionById(firstCondition.GetEvaluatedValue());
	ASSERT(pFstCondition != NULL);
	if(NULL == pFstCondition)
		return false;

	// Detect dead loop caused by the close loop reference. Such as A<-->B
	if(!sComplexConditionCloseLoopChecker.PushOngoingItem(GetObjectId()))
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
		bExist = GetParameter(SECOND_CONDITION, sndCondition);
		ASSERT(bExist);
		if(bExist)
		{
			Condition* pSndCondition = TaskManager::Get()->GetConditionById(sndCondition.GetEvaluatedValue());
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

BEHAVIOR_CLASS_IMP(FileExistsCondition, Condition)

bool FileExistsCondition::IsTrue()
{
    Parameter para;
    bool bExist = GetParameter(FILE_NAME, para);
    ASSERT(bExist);

    if(bExist)
        return PcUtil::DoesFileorFolderExist(para.GetEvaluatedValue());
    
    return false;
}

//////////////////////////////////////////////////////////////////////////
// FolderExistsCondition
//////////////////////////////////////////////////////////////////////////

BEHAVIOR_CLASS_IMP(FolderExistsCondition, Condition)

bool FolderExistsCondition::IsTrue()
{
    Parameter para;
    bool bExist = GetParameter(FOLDER_NAME, para);
    ASSERT(bExist);

    if(bExist)
        return PcUtil::DoesFileorFolderExist(para.GetEvaluatedValue());

    return false;
}
