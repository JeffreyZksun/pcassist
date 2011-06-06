// PC.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <list>
#include <iostream>

#include "DocumentManager.h"
#include "TaskManager.h"

void AnalyzeInputOptions(int argc, _TCHAR* argv[], ParameterObject& options);
void PrintHelp();

// Define the supported parameter names.
#define OPT_FILE _T("file") // Read FILE as the task schema.
#define OPT_HELP _T("help")

// The command line likes PC.exe File="C:\_DemoPcUsage.xml"
int _tmain(int argc, _TCHAR* argv[])
{
	ParameterObject options;

	AnalyzeInputOptions(argc, argv, options);

	bool bShowHelp = false;
	if(options.GetParameterLength() == 0)
	{
		bShowHelp = true;

	}
	else if (options.GetParameterLength() == 1)
	{
		Parameter para;
		bool bHasItem = options.GetParameter(OPT_HELP, para);
		if(bHasItem)
			bShowHelp = true;
	}

	if(bShowHelp)
	{
		PrintHelp();
		return 0;
	}

	Parameter fileName;
	bool bRet = options.GetParameter(OPT_FILE, fileName);
	if(!bRet)
	{
		PrintHelp();
		return 1;
	}

	DocumentManager* pDoc = new DocumentManager();
	pDoc->SetDocumentName(fileName.GetEvaluatedValue());
	pDoc->XmlIn();
	TaskManager::Get()->RunTasks();
	delete pDoc;

	return 0;
}

void AnalyzeInputOptions(int argc, _TCHAR* argv[], ParameterObject& options)
{
	// The first parameter is the command name itself.
	CString str;
	for(int i = 1; i < argc; i++)
	{
		// Find the assignment operator "="
		str = argv[i];
		int pos = str.Find(_T('='));
		if (-1 == pos) // not find
		{
			// Check if it's help;
			if(str.CompareNoCase(_T("\\?")) == 0 || str.CompareNoCase(_T("-?")) == 0)
			{
				options.AddParameter(Parameter(OPT_HELP, _T("")));
			}
			continue;
		}

		// Verify name is not empty
		CString varName = str.Left(pos);
		if(varName.GetLength() == 0)
			continue;

		// Verify value is not empty
		CString varValue = str.Right(str.GetLength() - pos - 1);
		if(varValue.GetLength() < 2)
			continue;

		// Add the parameter
		Parameter varPara(varName, varValue);
		options.AddParameter(varPara);
	}
}

void PrintHelp()
{
	std::cout << "Usage: PC [options...]\n";
	std::cout << "Options:\n";
	std::cout << "	-?, /?			Show help.\n";
	std::cout << "	file=FILE		Read FILE as the task schema.\n";
	std::cout << "\n";
	std::cout << "This program built for i386-pc\n";
	std::cout << "Report bugs to http://code.google.com/p/pcassist/issues/list\n";
}

