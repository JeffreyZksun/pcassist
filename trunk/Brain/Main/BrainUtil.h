#pragma once
#include "BrainSystem.h"

// Export the functions for the unit test purpose.
// Actually these functions should NOT be called outside this library.
namespace PcUtil
{
    // It just works for the local files, such as C:\content.txt.
    // But it doesn't work for the network shared file, such as \\dataServer\folder\content.txt
    BRAINEXPORT bool DoesLocalFileExist(const CString& fileFullName);
    BRAINEXPORT bool DoesLocalFolderExist(const CString& folderFullName);

    BRAINEXPORT bool DoesFileorFolderExist(const CString& fileFullName);

    BRAINEXPORT bool CopyFile(const CString& srcFileFullName, const CString& destFileFullName);
    BRAINEXPORT bool CopyFolder(const CString& srcFolderFullName, const CString& destFolderFullName);

    BRAINEXPORT bool DeleteFile(const CString& fileFullName);
    BRAINEXPORT bool DeleteFolder(const CString& folderFullName);

    BRAINEXPORT bool CreateFile(const CString& fileFullName);
    BRAINEXPORT bool CreateFolder(const CString& folderFullName);

    BRAINEXPORT bool MakeLink(const CString& link, const CString& target, bool bIsDirectory = true);

    BRAINEXPORT bool RunSystemCommand(const CString& cmd);
};

