#pragma once

#ifdef _WINOS

#include "OS\Windows\WindowsProvider.h"
#include <WinBase.h>
#include <lmcons.h>
#include "BrainUtil.h"

WindowsProvider::~WindowsProvider()
{

}

CString WindowsProvider::GetExeModulePath()
{
	TCHAR exeName[MAX_PATH];
	if (GetModuleFileName(NULL, exeName, MAX_PATH) != 0)
	{
		CString strExeName = exeName; // such as C:\Program file\PC.exe
		int pos = strExeName.ReverseFind(_T('\\'));
		CString strExePath = strExeName.Left(pos);

		return strExePath;
	}

	return _T("");
}

CString WindowsProvider::GetUserName()
{
	DWORD unMaxLength = UNLEN + 1;
	TCHAR userName [ UNLEN + 1 ];

	CString strUserName;
	if (::GetUserName( (TCHAR*)userName, &unMaxLength ))
		strUserName = userName;
	else
		strUserName = _T("UnknownUserName");

	return strUserName;
}

CString WindowsProvider::GetComputerName()
{
	// *ComputerName
	DWORD cnMaxLenggh = CNLEN + 1;
	TCHAR computerName[CNLEN + 1];
	CString strComputerName;
	if(::GetComputerName(computerName, &cnMaxLenggh))
		strComputerName = computerName;
	else
		strComputerName = _T("UnknownComputerName");

	return strComputerName;
}

CString WindowsProvider::GetPlatformString()
{
	// *Platform
	CString folderName = _T("C:\\Program Files (x86)");

	bool bIsx64 = BrainUtil::DoesFileorFolderExist(folderName);
	CString strPlatfrom = _T("x86");
	if(bIsx64)
		strPlatfrom = _T("x64");

	return strPlatfrom;
}

#endif //_WINOS