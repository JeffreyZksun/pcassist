#pragma once
#include "BrainSystem.h"

namespace BrainUtil
{
    // It just works for the local files, such as C:\content.txt.
    // But it doesn't work for the network shared file, such as \\dataServer\folder\content.txt
    bool DoesLocalFileExist(const CString& fileFullName);
    bool DoesLocalFolderExist(const CString& folderFullName);

    bool DoesFileorFolderExist(const CString& fileFullName);

    bool CopyFile(const CString& srcFileFullName, const CString& destFileFullName);
    bool CopyFolder(const CString& srcFolderFullName, const CString& destFolderFullName);

    bool DeleteFile(const CString& fileFullName);
    bool DeleteFolder(const CString& folderFullName);

    bool CreateFile(const CString& fileFullName);
    bool CreateFolder(const CString& folderFullName);

    bool MakeLink(const CString& link, const CString& target, bool bIsDirectory = true);

    bool RunSystemCommand(const CString& cmd);
	void LogOutLastError(const CString& lpszFunction);
};

