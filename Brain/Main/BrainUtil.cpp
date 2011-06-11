#include "StdAfx.h"
#include "BrainUtil.h"
#include <sys/stat.h> 
#include <windows.h>
#include <strsafe.h>
#include "Logger.h"

// GetParentFolderName(_T("C:\\RootFolder\\ChildFolder\\")); return C:\RootFolder\
// GetParentFolderName(_T("C:\\RootFolder\\ChildFolder\\readme.txt")); return C:\RootFolder\ChildFolder\
// GetParentFolderName(_T("RootFolder\\")); return .\
// The last char is always '\' in the return value.
CString GetParentFolderName(const CString& fileOrFolderName)
{
    CString tempName = fileOrFolderName;
    WCHAR lastChar = tempName.GetAt(tempName.GetLength() - 1);
    if(lastChar == _T('\\'))
        tempName.Truncate(tempName.GetLength() - 1); // delete the last '\'

    int lastPos = tempName.ReverseFind(_T('\\'));
    CString folderName(_T(".\\")); // current directory
    if(lastPos != -1)
        folderName = tempName.Left(lastPos + 1);

    return folderName;
}

bool BrainUtil::DoesLocalFileExist(const CString& fileFullName)
{
    CString tmpFileFullName = fileFullName;
    struct _stat stFileInfo;
    bool blnReturn;
    int intStat;

    // Attempt to get the file attributes
    intStat = _tstat(tmpFileFullName.GetBuffer(), &stFileInfo);
    if(intStat == 0 && (stFileInfo.st_mode & S_IFDIR) == 0) {
        // We were able to get the file attributes
        // so the file obviously exists.
        blnReturn = true;
    } else {
        // We were not able to get the file attributes.
        // This may mean that we don't have permission to
        // access the folder which contains this file. If you
        // need to do that level of checking, lookup the
        // return values of stat which will give you
        // more details on why stat failed.
        blnReturn = false;
    }

    return(blnReturn); 
}

bool BrainUtil::DoesLocalFolderExist(const CString& folderFullName)
{
    CString tmpFolderFullName = folderFullName;

    struct _stat stFileInfo;
    bool blnReturn;
    int intStat;

    // Attempt to get the file attributes
    intStat = _tstat(tmpFolderFullName.GetBuffer(), &stFileInfo);
    if(intStat == 0 && (stFileInfo.st_mode & S_IFDIR) != 0) {
        // We were able to get the file attributes
        // so the file obviously exists.
        blnReturn = true;
    } else {
        // We were not able to get the file attributes.
        // This may mean that we don't have permission to
        // access the folder which contains this file. If you
        // need to do that level of checking, lookup the
        // return values of stat which will give you
        // more details on why stat failed.
        blnReturn = false;
    }

    return(blnReturn); 
}

// BrainUtil::DoesFileorFolderExist(_T("\\\\dataServer\\Folder\\"));
// BrainUtil::DoesFileorFolderExist(_T("\\\\dataServer\\Folder\\readme.txt"));
// BrainUtil::DoesFileorFolderExist(_T("C:\\readme.txt"));
bool BrainUtil::DoesFileorFolderExist(const CString& fileFullName)
{
    CString tmpFileFullName = fileFullName;

    // http://msdn.microsoft.com/en-us/library/1w06ktdy%28v=vs.71%29.aspx
    //Return Value
    // Each function returns 0 if the file has the given mode. 
    // The function returns ? if the named file does not exist 
    // or is not accessible in the given mode; in this case, errno is set as follows: 

    //  mode value 	Checks file for
    //    00 	Existence only
    //    02 	Write permission
    //    04 	Read permission
    //    06 	Read and write permission
    int ret = _waccess(tmpFileFullName.GetBuffer(), 0x04);
    
    return 0 == ret;
}

// BrainUtil::CopyFile(_T("\\\\server\\dataFolder\\readme.log"), _T("C:\\readme.log"));
bool BrainUtil::CopyFile(const CString& srcFileFullName, const CString& destFileFullName)
{
    if(!DoesFileorFolderExist(srcFileFullName))
        return false;

    // http://msdn.microsoft.com/en-us/library/277bwbdz%28VS.71%29.aspx
    CString src = srcFileFullName;
    CString dest = destFileFullName;

    CString destFolderFullName = GetParentFolderName(destFileFullName);
    if(!DoesFileorFolderExist(destFolderFullName))
    {
        bool bRet = CreateFolder(destFolderFullName); // Create the parent directory tree.
        if(!bRet)
            return false;
    }

    CString cmd;
    cmd.Format(_T("copy \"%s\" \"%s\""), src.GetBuffer(), dest.GetBuffer());
    int ret = _wsystem(cmd.GetBuffer());
    ASSERT(0 == ret);
    bool bSucc = DoesFileorFolderExist(destFileFullName) && 0 == ret;
    return bSucc;
}

// BrainUtil::CopyFolder(_T("C:\\srcFolder\"), _T("C:\\destFolder\\"));
// BrainUtil::CopyFolder(_T("C:\\srcFolder"), _T("C:\\newFolderRoot\\newFolder\\destFolder"));
// The directory tree will be created by xcopy if the parent of the dest doesn't exist.
bool BrainUtil::CopyFolder(const CString& srcFolderFullName, const CString& destFolderFullName)
{
    if(!DoesFileorFolderExist(srcFolderFullName))
        return false;

    CString src = srcFolderFullName;
    WCHAR lastChar = src.GetAt(src.GetLength() - 1);
    if(lastChar != _T('\\'))
        src.AppendChar(_T('\\')); 
    src.Append(_T("*.*")); // Add the widechar, change the format to be like C:\srcFolder\*.*

    CString dest = destFolderFullName;
    // If the last char isn't '\', a dialog will pop up to specify if the name is file or folder.
    // Add the ending '\'. change the format to be like C:\destFolder\ 
    lastChar = dest.GetAt(dest.GetLength() - 1);
    if(lastChar != _T('\\'))
        dest.AppendChar(_T('\\')); 

    CString cmd;
    cmd.Format(_T("xcopy \"%s\" \"%s\" /E /C /R /Q /Y"), src.GetBuffer(), dest.GetBuffer());
    int ret = _wsystem(cmd.GetBuffer());
    ASSERT(0 == ret);
    bool bSucc = DoesFileorFolderExist(destFolderFullName) && 0 == ret;
    return bSucc;
}

// BrainUtil::DeleteFile(_T("C:\\readme.txt"));
bool BrainUtil::DeleteFile(const CString& fileFullName)
{
    if(!DoesFileorFolderExist(fileFullName))
        return true;

    CString name = fileFullName;
    CString cmd;
    cmd.Format(_T("del \"%s\" /F /Q"), name.GetBuffer());
    int ret = _wsystem(cmd.GetBuffer());
    ASSERT(0 == ret);
    bool bSucc = !DoesFileorFolderExist(fileFullName);
    return bSucc;
}
// BrainUtil::DeleteFolder(_T("C:\\DestFolder\\"));
// BrainUtil::DeleteFolder(_T("C:\\DestFolder"));
bool BrainUtil::DeleteFolder(const CString& folderFullName)
{
    if(!DoesFileorFolderExist(folderFullName))
        return true;

    CString name = folderFullName;
    CString cmd;
    cmd.Format(_T("rd \"%s\" /S /Q"), name.GetBuffer());
    int ret = _wsystem(cmd.GetBuffer());
    ASSERT(0 == ret);
    bool bSucc = !DoesFileorFolderExist(folderFullName);
    return bSucc;
}

// BrainUtil::CreateFile(_T("C:\\newFolderRoot\\newFolder\\newFile.txt"));
bool BrainUtil::CreateFile(const CString& fileFullName)
{
    if(DoesFileorFolderExist(fileFullName))
        return true;

    CString folderFullName = GetParentFolderName(fileFullName);
    if(!DoesFileorFolderExist(folderFullName))
    {
        bool bRet = CreateFolder(folderFullName); // Create the parent directory tree.
        if(!bRet)
            return false;
    }

    CString name = fileFullName;
    CString cmd;
    cmd.Format(_T("echo \"\" >> \"%s\""), name.GetBuffer());
    int ret = _wsystem(cmd.GetBuffer());
    ASSERT(0 == ret);
    bool bSucc = DoesFileorFolderExist(fileFullName);
    return bSucc;
}

// md "C:\newFolderRoot\newFolder\destFolder"
// BrainUtil::CreateFolder(_T("C:\\newFolderRoot\\newFolder\\destFolder"));
// The directory tree will be created if the parent doesn't exist. This is done by the md command.
bool BrainUtil::CreateFolder(const CString& folderFullName)
{
    if(DoesFileorFolderExist(folderFullName))
        return true;

    CString name = folderFullName;
    CString cmd;
    cmd.Format(_T("md \"%s\""), name.GetBuffer());
    int ret = _wsystem(cmd.GetBuffer());
    ASSERT(0 == ret);
    bool bSucc = DoesFileorFolderExist(folderFullName);
    return bSucc;
}

// mklink /D "C:\existingFolder\Link" "C:\Target"
// mklink /D "C:\existingFolder\Link\" "C:\Target\"
// The ending slash is optional. The parent directory of the link must exist.
bool BrainUtil::MakeLink(const CString& link, const CString& target, bool bIsDirectory/* = true*/)
{
    CString temLink = link;
    CString temTarget = target;

    // delete the last '\'
    WCHAR lastChar = temLink.GetAt(temLink.GetLength() - 1);
    if(lastChar == _T('\\'))
        temLink.Truncate(temLink.GetLength() - 1); 

    if(DoesFileorFolderExist(temLink))
    {
        // Delete the link
        // For links to directories: rmdir linkname
        // For links to files: del linkname
        CString tmpCmd;
        tmpCmd.Format(_T("rmdir \"%s\""), temLink.GetBuffer());
        RunSystemCommand(tmpCmd);

        if(DoesFileorFolderExist(temLink)) // If still exist it might be a file link
        {
            tmpCmd.Format(_T("del \"%s\""), temLink.GetBuffer());
            RunSystemCommand(tmpCmd);
        }

        if(DoesFileorFolderExist(temLink))// check again
        {
            ASSERT(false); 
            return false;
        }
    }
    else
    {
        CString folderFullName = GetParentFolderName(link);
        if(!DoesFileorFolderExist(folderFullName))
        {
            bool bRet = CreateFolder(folderFullName); // Create the parent directory tree.
            if(!bRet)
                return false;
        }
    }

    CString cmd;
    if(bIsDirectory)
        cmd.Format(_T("mklink /D \"%s\" \"%s\""), temLink.GetBuffer(), temTarget.GetBuffer());
    else
        cmd.Format(_T("mklink \"%s\" \"%s\""), temLink.GetBuffer(), temTarget.GetBuffer());

    int ret = _wsystem(cmd.GetBuffer());
    ASSERT(0 == ret);
    bool bSucc = DoesFileorFolderExist(link);
    return bSucc;
}

bool BrainUtil::RunSystemCommand(const CString& cmd)
{
    CString tempCmd = cmd;
    int ret = _wsystem(tempCmd.GetBuffer());
    //ASSERT(0 == ret); // Don't aseert the failure is accepted.
    return 0 == ret;
}

void BrainUtil::LogOutLastError(const CString& lpszFunction)
{
	// Retrieve the system error message for the last-error code

	LPVOID lpMsgBuf;
	LPVOID lpDisplayBuf;
	DWORD dw = GetLastError(); 

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | 
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		dw,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR) &lpMsgBuf,
		0, NULL );

	// Display the error message and exit the process

	lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT, 
		(lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR)); 
	StringCchPrintf((LPTSTR)lpDisplayBuf, 
		LocalSize(lpDisplayBuf) / sizeof(TCHAR),
		TEXT("%s failed with error %d: %s"), 
		(LPCTSTR)lpszFunction, dw, lpMsgBuf); 
	LogOut((LPTSTR)lpDisplayBuf, COLOR_RED);

	LocalFree(lpMsgBuf);
	LocalFree(lpDisplayBuf);
	//ExitProcess(dw); 
}
