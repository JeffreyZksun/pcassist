// PC.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <list>
#include <algorithm>

#include "TaskSystem.h"
#include "BehaviorManager.h"
#include "Logger.h"

#include "CmdOption.h"
#include "CmdLineMgr.h"

using namespace Ts;

// We need to include the static lib and all the obj files contain the global objects. (Action.obj Condition.obj)
// If only include the static lib, the global objects won't be initialized.
// This results in the actions and conditions can't register themselves.
// http://social.msdn.microsoft.com/Forums/en/vclanguage/thread/5c5ee89d-2a38-483d-8550-484550901170


void PrintHelp(const Ts::CmdLineMgr&);


#define PC_VERSION _T("(v1.15)")
#define OPT_FILE ("file") // Read FILE as the task schema.
#define OPT_HELP ("help")
#define OPT_SHOW_PARAMETER ("show-parameters")

static TaskSystem	brainApp;

// The command line likes PC -F "C:\_DemoPcUsage.xml"
int main(int argc, const char* const argv[])
{	
	Ts::CmdLineMgr cmdMgr;
	{
		CmdOption* pOption = new CmdOption(OPT_HELP, '?', "Display help message", CmdOption::eNoValue);
		bool ok = cmdMgr.AddSupportedOption(pOption);
		if(!ok)
			delete pOption;
	}

	{
		CmdOption* pOption = new CmdOption(OPT_FILE, 'F', "The script xml file name");
		bool ok = cmdMgr.AddSupportedOption(pOption);
		if(!ok)
			delete pOption;
	}

	{
		CmdOption* pOption = new CmdOption(OPT_SHOW_PARAMETER, "Log out the value of the parameters", CmdOption::eNoValue);
		bool ok = cmdMgr.AddSupportedOption(pOption);
		if(!ok)
			delete pOption;
	}


	const bool ok = cmdMgr.Parse(argc, argv);

	if(!ok)
	{
		LogOut(_T("Failed to parse the command line options\n\n"));
		PrintHelp(cmdMgr);

		return 1;
	}

	if(cmdMgr.HasUnrecognizedOption())
	{
		const NString& invalidOpt = cmdMgr.GetUnrecongnizedOption();

		CString prompt;
		prompt.Format(_T("PC: invalid options %s\n\n"), invalidOpt);
		LogOut(prompt);
		PrintHelp(cmdMgr);

		return 1;
	}

	if(cmdMgr.GetRecognizedOptionByName(OPT_HELP))
	{
		PrintHelp(cmdMgr);

		return 0;
	}

	CmdOption* pFileOpt = cmdMgr.GetRecognizedOptionByName(OPT_FILE);
	if(!pFileOpt)
	{
		LogOut(_T("Error: script xml file name isn't specified\n\n"));
		PrintHelp(cmdMgr);
		return 1;
	}

	CmdOption* pShowParametersOpt = cmdMgr.GetRecognizedOptionByName(OPT_SHOW_PARAMETER);
	if(pShowParametersOpt)
		Logger::Get()->SetDoesOutputParameter(true);
	else
		Logger::Get()->SetDoesOutputParameter(false);

	const NString& fileName = pFileOpt->GetValue();
	WString wstr(fileName.begin(), fileName.end());
	CString cstrFileName = wstr.c_str();

	const bool bRet = brainApp.XmlIn(cstrFileName);

	if(bRet)
		brainApp.GetBehaviorManager()->RunTasks();
	else
	{
		LogOut(_T("Can't open file: "), COLOR_RED);
		LogOut(cstrFileName, COLOR_RED);
		LogOut(_T("\n"));
	}
	
	return 0;
}

void PrintHelp(const Ts::CmdLineMgr& cmdMgr)
{
	const NString options_Desc = cmdMgr.GetOptionDescription();

	WString wstr(options_Desc.begin(), options_Desc.end());
	CString cstrDesc = wstr.c_str();	

	LogOut(_T("Usage: PC [options...]\n"));

	LogOut(cstrDesc);

	LogOut(_T("\n"));
	LogOut(_T("This program built for i386-pc. "));
	LogOut(PC_VERSION);
	LogOut(_T("\n"));
	LogOut(_T("Report bugs to http://code.google.com/p/pcassist/issues/list\n"));
}