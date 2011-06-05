#include "StdAfx.h"
#include "Condition.h"
#include "BrainUtil.h"
#include "ConstantsDefinition.h"


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

	// ToDo - We should check cross reference, which will result in dead loop.
	if(oper.GetEvaluatedValue().CompareNoCase(_T("Not")) == 0)
	{
		return !pFstCondition->IsTrue();
	}
	else 
	{
		Parameter sndCondition;
		bExist = GetParameter(SECOND_CONDITION, sndCondition);
		ASSERT(bExist);
		if(!bExist)
			return false;

		Condition* pSndCondition = TaskManager::Get()->GetConditionById(sndCondition.GetEvaluatedValue());
		ASSERT(pSndCondition != NULL);
		if(NULL == pSndCondition)
			return false;

		if(oper.GetEvaluatedValue().CompareNoCase(_T("AND")) == 0)
		{
			return pFstCondition->IsTrue() && pSndCondition->IsTrue();
		}
		else if(oper.GetEvaluatedValue().CompareNoCase(_T("OR")) == 0)
		{
			return pFstCondition->IsTrue() || pSndCondition->IsTrue();
		}
	}

	return false;
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
