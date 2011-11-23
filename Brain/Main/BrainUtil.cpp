#include "StdAfx.h"
#include "BrainUtil.h"
#include <sys/stat.h> 
#include <windows.h>
#include <strsafe.h>
#include "Logger.h"

#include <Psapi.h> // EnumProcesses, Link Psapi.lib

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
    //int ret = _wsystem(tempCmd.GetBuffer());
    //ASSERT(0 == ret); // Don't aseert the failure is accepted.

	// Get the output from the pipe
	FILE* pipe = _wpopen(tempCmd.GetBuffer(), _T("r"));
	if (!pipe) 
	{
		return false;
		LogOut(_T("Error: failed to create the piple."));
	}

	TCHAR buffer[256];
	while(!feof(pipe)) {
		if(fgetws(buffer, 256, pipe) != NULL)
		{
			LogOut(buffer);
		}
	}
	int ret = _pclose(pipe);

    return 0 == ret;
}

// Return error level.
// Refer to http://msdn.microsoft.com/en-us/library/ms682499%28VS.85%29.aspx
// For the stream indirection.
unsigned long BrainUtil::RunProcess(const CString& applicationName
    , const CString& applicationParameter
    , bool bShowWindow
    , bool bWaitForExit)
{

    // http://msdn.microsoft.com/en-us/library/ms682425%28v=vs.85%29.aspx
    // Create process
    //
    STARTUPINFO startupInfo;
    memset(&startupInfo, 0, sizeof(startupInfo));
    startupInfo.cb = sizeof(STARTUPINFO);
    startupInfo.dwFlags = STARTF_USESHOWWINDOW;
    startupInfo.wShowWindow = bShowWindow ? SW_NORMAL : SW_HIDE;

    PROCESS_INFORMATION processInformation;

    // We need the application name is the first parameter
    // When there is parameter, we need start the process with cmd line only.
    // We need to avoid the case below.

    //Test Running...
    //	AppName:  C:\CreateProcessBug\Debug\ParamTest.exe
    //	CmdLine:  Param1 Param2 Param3
    //ParamTest Output:
    //	Number of parameters: 3
    //	Parameter Info:
    //		Param #0: Param1
    //		Param #1: Param2
    //		Param #2: Param3

    CString cmdLine;
    BOOL ret = FALSE;
    if(applicationParameter.IsEmpty())
    {
        //Test Running...
        //	AppName:  C:\CreateProcessBug\Debug\ParamTest.exe
        //	CmdLine:  (null)
        //ParamTest Output:
        //	Number of parameters: 1
        //	Parameter Info:
        //		Param #0: C:\CreateProcessBug\Debug\ParamTest.exe
        ret = CreateProcess((LPCTSTR)applicationName, NULL, NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, &startupInfo, &processInformation);
    }
    else
    {
        //Test Running...
        //	AppName:  (null)
        //	CmdLine:  "C:\CreateProcessBug\Debug\ParamTest.exe" Param1 Param2 Param3
        //ParamTest Output:
        //	Number of parameters: 4
        //	Parameter Info:
        //		Param #0: C:\CreateProcessBug\Debug\ParamTest.exe
        //		Param #1: Param1
        //		Param #2: Param2
        //		Param #3: Param3

        cmdLine = applicationName + _T(" ") + applicationParameter;

        TCHAR tempCmdLine[MAX_PATH * 2];  //Needed since CreateProcessW may change the contents of CmdLine
        _tcscpy_s(tempCmdLine, MAX_PATH *2, (LPCTSTR)cmdLine);

        ret = CreateProcess(NULL, tempCmdLine, NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, &startupInfo, &processInformation);
    }

    if (!ret || !processInformation.hThread || !processInformation.hProcess)
    {
        return GetLastError(); // Fail
    }

    if(bWaitForExit)
        WaitForSingleObject( processInformation.hProcess, INFINITE );

    CloseHandle( processInformation.hProcess );
    CloseHandle( processInformation.hThread );

    return 0; // Success
}

void BrainUtil::LogOutLastError(const CString& lpszFunction)
{
	// Retrieve the system error message for the last-error code

	LPVOID lpMsgBuf;
	LPVOID lpDisplayBuf;
	DWORD dw = GetLastError(); 

	if(0 == dw)
		return; // Don't need to log out the success information.

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

bool BrainUtil::IsProcessRunning(const CString &strProcessName, bool bCompareNameOnly)
{
	// Get the list of process identifiers.
	DWORD dwProcesses[2048];
	DWORD dwSizeNeeded = 0;
	DWORD dwProcessesCount = 0;
	if ( !EnumProcesses( dwProcesses, sizeof(dwProcesses), &dwSizeNeeded ) )
	{
		return false;
	}

	dwProcessesCount = dwSizeNeeded / sizeof(DWORD);
	CString strToCheck = strProcessName;
	strToCheck.MakeLower();

	for(int i=0; i<(int)dwProcessesCount; i++ )
	{        
		if( dwProcesses[i] != 0 )
		{
			HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, dwProcesses[i]);
			if(hProcess)
			{
				HMODULE hModule = NULL;
				dwSizeNeeded = 0;
				TCHAR cName[MAX_PATH];
				if(EnumProcessModules(hProcess, &hModule, sizeof(DWORD), &dwSizeNeeded) )
				{                
					if(GetModuleFileNameEx(hProcess, hModule, cName, MAX_PATH ) != 0)
					{
						CString strFullName(cName); // C:\Windows\SysWOW64\vmnat.exe

						CString strProcName = strFullName;
						if(bCompareNameOnly)
						{
							int pos = strFullName.ReverseFind('\\');

							if(-1 != pos)
								strProcName = strFullName.Right(strFullName.GetLength() - pos - 1);
						}

						strProcName.MakeLower();
						if(strProcName == strToCheck)
							return true;
					}
				}
				CloseHandle(hProcess);

			}
		}
	}
	return false;
} 
