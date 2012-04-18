// TaskServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <list>
#include <algorithm>

#include "TaskSystem.h"
#include "BehaviorManager.h"
#include "Logger.h"
#include "TCPServer.h"

#include "MessageResource.h"
#include "EventSinks.h"


using namespace Ts;


void PrintHelp(const Ts::CmdLineMgr&);


#define PRODUCT_VERSION _T("(v1.0)")
#define OPT_PORT ("port") // Read FILE as the task schema.
#define OPT_HELP ("help")


static TaskSystem	taskSystem;

int main(int argc, const char* const argv[])
{	
	unsigned short portNumber;
	{
		Ts::CmdLineMgr cmdMgr;
		{
			CmdOption* pOption = new CmdOption(OPT_HELP, '?', "Display help message", CmdOption::eNoValue);
			bool ok = cmdMgr.AddSupportedOption(pOption);
			if(!ok)
				delete pOption;
		}

		{
			CmdOption* pOption = new CmdOption(OPT_PORT, 'P', "The server port");
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
			prompt.Format(_T("TaskServer: invalid options %s\n\n"), invalidOpt);
			LogOut(prompt);
			PrintHelp(cmdMgr);

			return 1;
		}

		if(cmdMgr.GetRecognizedOptionByName(OPT_HELP))
		{
			PrintHelp(cmdMgr);

			return 0;
		}

		CmdOption* pPortOpt = cmdMgr.GetRecognizedOptionByName(OPT_PORT);
		if(!pPortOpt)
		{
			LogOut(_T("Error: server port isn't specified\n\n"));
			PrintHelp(cmdMgr);
			return 1;
		}

		const NString& strPort = pPortOpt->GetValue();

		std::istringstream istr(strPort.c_str());
		istr >> portNumber;
		if(0 == portNumber)
		{
			LogOut(_T("Error: Invalid port\n\n"));
			PrintHelp(cmdMgr);
			return 1;
		}
	}

	// ToDo - Add the action and conditions
	{

	}

	// Start the task manager
	{
		taskSystem.GetTaskManager()->Start();
	}

	// Subscribe the event
	RemoteMessageSink msgSink (&taskSystem);
	ConnectionMonitorSink monitorSink;

	// Start the network server
	TCPServerPtr pServer = TCPServer::Create(portNumber);
	pServer->Start();

	// Display the welcome message
	std::wcout << MessageResource::GetWelcomeMesage();
	std::wcout << _T("\r\n");
	std::wcout << _T("Server is listening on port ") << portNumber << std::endl;

	// Loop to get the command from the server console 
	char line[256];
	while (std::cin.getline(line, 256))
	{
		std::cout << line << std::endl;
	}
	
	return 0;
}

void PrintHelp(const Ts::CmdLineMgr& cmdMgr)
{
	const NString options_Desc = cmdMgr.GetOptionDescription();

	WString wstr(options_Desc.begin(), options_Desc.end());
	CString cstrDesc = wstr.c_str();	

	LogOut(_T("Usage: TaskServer [options...]\n"));

	LogOut(cstrDesc);

	LogOut(_T("\n"));
	LogOut(_T("This program built for i386-pc. "));
	LogOut(PRODUCT_VERSION);
	LogOut(_T("\n"));
}