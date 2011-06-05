#include "StdAfx.h"
#include "Action.h"
#include "BrainUtil.h"
#include "ConstantsDefinition.h"

BEHAVIOR_CLASS_IMP(ComplexAction, Action)

bool ComplexAction::Execute()
{
	// Condition
	Parameter condition;
	bool bExist = GetParameter(EXECUTE_CONDITION, condition);
	ASSERT(bExist);
	if(!bExist)
		return false;

	Condition* pExeCondition = TaskManager::Get()->GetConditionById(condition.GetEvaluatedValue());
	ASSERT(pExeCondition != NULL);
	if(NULL == pExeCondition)
		return false;

	if(!pExeCondition->IsTrue()) // The condition isn't meet. Don't run return true.
		return true;

	// Main action, required.
	Parameter mainAction;
	bExist = GetParameter(MAIN_ACTION, mainAction);
	ASSERT(bExist);
	if(!bExist)
		return false;

	Action* pMainAction = TaskManager::Get()->GetActionById(mainAction.GetEvaluatedValue());
	ASSERT(pMainAction != NULL);
	if(NULL == pMainAction)
		return false;

	// Pre action, optional.
	Parameter preAction;
	bExist = GetParameter(PRE_ACTION, preAction);
	if(bExist)
	{
		Action* pPreAction = TaskManager::Get()->GetActionById(preAction.GetEvaluatedValue());
		if(pPreAction != NULL)
			pPreAction->Execute();
	}

	// Main action
	bool bRet = pMainAction->Execute();

	// Post action, optional.
	Parameter postAction;
	bExist = GetParameter(POST_ACTION, postAction);
	if(bExist)
	{
		Action* pPostAction = TaskManager::Get()->GetActionById(postAction.GetEvaluatedValue());
		if(pPostAction != NULL)
			pPostAction->Execute();
	}

	return bRet;
}

BEHAVIOR_CLASS_IMP(CreateFileAction, Action)

bool CreateFileAction::Execute()
{
    Parameter para;
    bool bExist = GetParameter(FILE_NAME, para);
    ASSERT(bExist);

    if(bExist)
        return PcUtil::CreateFile(para.GetEvaluatedValue());

    return false;
}

BEHAVIOR_CLASS_IMP(DeleteFileAction, Action)

bool DeleteFileAction::Execute()
{
    Parameter para;
    bool bExist = GetParameter(FILE_NAME, para);
    ASSERT(bExist);

    if(bExist)
        return PcUtil::DeleteFile(para.GetEvaluatedValue());

    return false;
}

BEHAVIOR_CLASS_IMP(CopyFileAction, Action)

bool CopyFileAction::Execute()
{
    Parameter para1;
    bool bExist = GetParameter(SRC_FILE_NAME, para1);
    ASSERT(bExist);
    if(!bExist)
        return false;

    Parameter para2;
    bExist = GetParameter(DEST_FILE_NAME, para2);
    ASSERT(bExist);
    if(!bExist)
        return false;

    return PcUtil::CopyFile(para1.GetEvaluatedValue(), para2.GetEvaluatedValue());
}

BEHAVIOR_CLASS_IMP(CreateFolderAction, Action)

bool CreateFolderAction::Execute()
{
    Parameter para;
    bool bExist = GetParameter(FOLDER_NAME, para);
    ASSERT(bExist);

    if(bExist)
        return PcUtil::CreateFolder(para.GetEvaluatedValue());

    return false;
}

BEHAVIOR_CLASS_IMP(DeleteFolderAction, Action)

bool DeleteFolderAction::Execute()
{
    Parameter para;
    bool bExist = GetParameter(FOLDER_NAME, para);
    ASSERT(bExist);

    if(bExist)
        return PcUtil::DeleteFolder(para.GetEvaluatedValue());

    return false;
}

BEHAVIOR_CLASS_IMP(CopyFolderAction, Action)

bool CopyFolderAction::Execute()
{
    Parameter para1;
    bool bExist = GetParameter(SRC_Folder_NAME, para1);
    ASSERT(bExist);
    if(!bExist)
        return false;

    Parameter para2;
    ASSERT(bExist);
    bExist = GetParameter(DEST_Folder_NAME, para2);
    if(!bExist)
        return false;

    return PcUtil::CopyFolder(para1.GetEvaluatedValue(), para2.GetEvaluatedValue());
}

BEHAVIOR_CLASS_IMP(MakeDirectoryLinkAction, Action)

bool MakeDirectoryLinkAction::Execute()
{
    Parameter para1;
    bool bExist = GetParameter(LINK_NAME, para1);
    ASSERT(bExist);
    if(!bExist)
        return false;

    Parameter para2;
    ASSERT(bExist);
    bExist = GetParameter(LINK_TARGET, para2);
    if(!bExist)
        return false;

    return PcUtil::MakeLink(para1.GetEvaluatedValue(), para2.GetEvaluatedValue());
}

