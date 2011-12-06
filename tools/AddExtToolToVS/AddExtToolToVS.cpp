// AddExtToolToVS.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <atlstr.h> // CString
#include "Logger.h"

#define EXE_VERSION _T("(v1.0)")
void PrintHelp();

int _tmain(int argc, _TCHAR* argv[])
{
	if(argc < 5)
	{
		PrintHelp();
		return 1;
	}

	return 0;
}


void PrintHelp()
{
	LogOut(_T("Usage: AddExtToolToVS title=Title command=Command arguments=Arguments directory=InitialDirectory\n"));
	LogOut(_T("\n"));
	LogOut(_T("This program built for i386-pc. "));
	LogOut(EXE_VERSION);
	LogOut(_T("\n"));
	LogOut(_T("Report bugs to http://code.google.com/p/pcassist/issues/list\n"));
}

