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
