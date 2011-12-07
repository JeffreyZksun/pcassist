// AddExtToolToVS.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <atlstr.h> // CString
#include "Logger.h"

#include "CommandLineService.h"
#include "RegistryKey.h"

// Add the lib Psapi.lib for APIs GetModuleFileNameEx, EnumProcessModules, EnumProcesses

#define EXE_VERSION _T("(v1.0)")

#define TITLE _T("title")
#define COMMAND _T("command")
#define ARGUMENTS _T("arguments")
#define DIRECTORY _T("directory")


class ClientService: public CommandLineService
{
public:
	virtual void		PrintHelp() 
	{
		LogOut(_T("Usage: AddExtToolToVS title=Title command=Command arguments=Arguments directory=InitialDirectory\n"));
		LogOut(_T("\n"));
		LogOut(_T("This program built for i386-pc. "));
		LogOut(EXE_VERSION);
		LogOut(_T("\n"));
		LogOut(_T("Report bugs to http://code.google.com/p/pcassist/issues/list\n"));
	}

	virtual CString		GetVersion() 
	{
		return EXE_VERSION;
	}
};


int _tmain(int argc, _TCHAR* argv[])
{
	ClientService cmdSrv;
	cmdSrv.AddSupportedArgumentName(TITLE);
	cmdSrv.AddSupportedArgumentName(COMMAND);
	cmdSrv.AddSupportedArgumentName(ARGUMENTS);
	cmdSrv.AddSupportedArgumentName(DIRECTORY);

	cmdSrv.AnalyzeArguments(argc, argv);

	if(cmdSrv.HasInvalidArguments())
	{
		LogOut(_T("Invalid arugments: "));
		LogOut(cmdSrv.GetInvalidArguments());
		LogOut(_T("\n"));

		cmdSrv.PrintHelp();
		return 1;
	}

	if(cmdSrv.GetArgementsLength() < 4)
	{
		cmdSrv.PrintHelp();
		return 1;
	}



	return 0;
}

// vsVersion 10.0 9.0
void AddExternalToolsToVs(const CString& title, const CString& command, const CString& arg, const CString& dir, const CString& vsVersion)
{
	CString vsRegPath = _T("Software\\Microsoft\\VisualStudio\\"); // HKEY_CURRENT_USER
	vsRegPath.Append(vsVersion);
	vsRegPath.Append(_T("External Tools"));

	RegistryKey toolKey;
	BOOL bRet = toolKey.OpenEx(HKEY_CURRENT_USER, vsRegPath, KEY_READ|KEY_WOW64_64KEY);

}
