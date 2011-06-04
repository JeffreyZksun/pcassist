#include "StdAfx.h"
#include "Action.h"
#include "BrainUtil.h"
#include "ConstantsDefinition.h"


bool CreateFileAction::Execute()
{
    Parameter para;
    bool bExist = GetParameter(FILE_NAME, para);
    ASSERT(bExist);

    if(bExist)
        return PcUtil::CreateFile(para.GetEvaluatedValue());

    return false;
}

bool DeleteFileAction::Execute()
{
    Parameter para;
    bool bExist = GetParameter(FILE_NAME, para);
    ASSERT(bExist);

    if(bExist)
        return PcUtil::DeleteFile(para.GetEvaluatedValue());

    return false;
}

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

bool CreateFolderAction::Execute()
{
    Parameter para;
    bool bExist = GetParameter(FOLDER_NAME, para);
    ASSERT(bExist);

    if(bExist)
        return PcUtil::CreateFolder(para.GetEvaluatedValue());

    return false;
}

bool DeleteFolderAction::Execute()
{
    Parameter para;
    bool bExist = GetParameter(FOLDER_NAME, para);
    ASSERT(bExist);

    if(bExist)
        return PcUtil::DeleteFolder(para.GetEvaluatedValue());

    return false;
}

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

