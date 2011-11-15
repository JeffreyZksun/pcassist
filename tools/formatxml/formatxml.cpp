// formatxml.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <objbase.h> // CoInitialize
#include <XmlIOStream.h> 
#include <atlstr.h> // CString
#include "Logger.h"

#define EXE_VERSION _T("(v1.0)")
void PrintHelp();

int _tmain(int argc, _TCHAR* argv[])
{
	if(argc < 3)
	{
		PrintHelp();
		return 1;
	}

	::CoInitialize(NULL);

	XmlIOStream* pXmlIOStream = new XmlIOStream(true);
	bool bRet = pXmlIOStream->Load(argv[1]); 
	if(!bRet)
		return 2;

	bRet = pXmlIOStream->Save(argv[2]);
	if(!bRet)
		return 3;

	::CoUninitialize();

	return 0;
}


void PrintHelp()
{
	LogOut(_T("Usage: formatxml inputxmlfile outputxmlfile\n"));
	LogOut(_T("\n"));
	LogOut(_T("This program built for i386-pc. "));
	LogOut(EXE_VERSION);
	LogOut(_T("\n"));
	LogOut(_T("Report bugs to http://code.google.com/p/pcassist/issues/list\n"));
}
