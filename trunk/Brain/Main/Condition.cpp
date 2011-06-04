#include "StdAfx.h"
#include "Condition.h"
#include "BrainUtil.h"
#include "ConstantsDefinition.h"


//////////////////////////////////////////////////////////////////////////
// FileExistsCondition
//////////////////////////////////////////////////////////////////////////

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

bool FolderExistsCondition::IsTrue()
{
    Parameter para;
    bool bExist = GetParameter(FOLDER_NAME, para);
    ASSERT(bExist);

    if(bExist)
        return PcUtil::DoesFileorFolderExist(para.GetEvaluatedValue());

    return false;
}
