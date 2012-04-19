// TaskServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <list>
#include <algorithm>

#include "ITaskManager.h"
#include "TaskSystem.h"
#include "BehaviorManager.h"
#include "Logger.h"
#include "TCPServer.h"

#include "MessageResource.h"
#include "EventSinks.h"
#include "TextCommandParser.h"


using namespace Ts;

static TaskSystem	taskSystem;
TextCommandParser	cmdParser;

int main(int argc, const char* const argv[])
{	
	unsigned short portNumber = 0;
	{

		const bool ok = cmdParser.ParseProgramOptions(argc, argv, portNumber);
		if(!ok)
			return 1;

		if(0 == portNumber)
			return 1;
	}

	// ToDo - Add the action and conditions
	{
		// Load script
	}

	// Start the task manager
	{
		taskSystem.GetTaskManager()->Start();
	}

	// Subscribe the event
	RemoteMessageSink msgSink (&taskSystem, &cmdParser);
	ConnectionMonitorSink monitorSink(&cmdParser);

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
		Ts::CmdLineMgr::pointer pCmdLineMgr = cmdParser.GetServerCmdLineMgr();
		if(!pCmdLineMgr)
			continue;

		bool ok = pCmdLineMgr->Parse(line);
		if(!ok)
		{
			LogOut(_T("Failed to parse the options\r\n"));
			continue;
		}

		if(pCmdLineMgr->HasUnrecognizedOption())
		{
			Ts::StringUtil util;

			const NString& invalidOpt = pCmdLineMgr->GetUnrecongnizedOption();

			CString prompt;
			prompt.Format(_T("Invalid options: %s\r\n\r\n"), util.convert_to_wstring(invalidOpt).data());
			LogOut(util.convert_to_wstring(prompt));


			continue;
		}

		if(pCmdLineMgr->GetRecognizedOptionByName(OPT_HELP))
		{
			LogOut(_T("Show help\r\n"));

			continue;
		}

		if(pCmdLineMgr->GetRecognizedOptionByName(OPT_QUIT))
		{
			pServer->Close();
			taskSystem.GetTaskManager()->Stop();

			break;
		}

		// ToDo -add task
		std::cout << line << std::endl;
	}
	
	return 0;
}
