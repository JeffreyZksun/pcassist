// PC.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <list>
#include <algorithm>
#include <iostream>

#include "DocumentManager.h"
#include "TaskManager.h"

void AnalyzeInputOptions(int argc, _TCHAR* argv[], ParameterObject& options);
void PrintHelp();
bool IsValidOption(const CString& option);
void InitializeValidOptions();
void AppendParameterValue(Parameter& para, CString& appendedValue);

// define the valid options
static std::list<CString> sValidOptions;

// Define the supported parameter names.
#define INVALID_OPTS _T("InvalidOptions") // Collect the invalid options
#define OPT_FILE _T("file") // Read FILE as the task schema.
#define OPT_HELP _T("help")

// The command line likes PC File="C:\_DemoPcUsage.xml"
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

	{
		Parameter para;
		bool bHasItem = options.GetParameter(INVALID_OPTS, para);
		if(bHasItem)
		{
			CString prompt;
			prompt.Format(_T("PC: invalid options %s\n"), para.GetRawdValue());
			std::wcout <<  (LPCTSTR)prompt;
			bShowHelp = true;
		}
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
	Parameter invalidOptions(INVALID_OPTS, _T(""));
	CString str;
	for(int i = 1; i < argc; i++)
	{
		// Find the assignment operator "="
		str = argv[i];
		int pos = str.Find(_T('='));
		if (-1 == pos) // not find
		{
			// Check if it's help;
			if(str.CompareNoCase(_T("/?")) == 0 || str.CompareNoCase(_T("-?")) == 0)
			{
				options.AddParameter(Parameter(OPT_HELP, _T("")));
			}
			else // Invalid
			{
				AppendParameterValue(invalidOptions, str);
			}
			continue;
		}

		// Verify name is not empty
		CString varName = str.Left(pos);
		if(varName.IsEmpty())
		{
			AppendParameterValue(invalidOptions, str);
			continue;
		}

		// Verify value is not empty
		CString varValue = str.Right(str.GetLength() - pos - 1);
		if(varValue.IsEmpty())
		{
			AppendParameterValue(invalidOptions, str);
			continue;
		}

		if(IsValidOption(varName))
		{
			// Add the parameter
			Parameter varPara(varName, varValue);
			options.AddParameter(varPara);
		}
		else
		{
			AppendParameterValue(invalidOptions, str);
		}
	}

	if(!invalidOptions.GetRawdValue().IsEmpty())
		options.AddParameter(invalidOptions);
}

void PrintHelp()
{
	std::wcout << "Usage: PC [options...]\n";
	std::wcout << "Options:\n";
	std::wcout << "	-?, /?			Show help.\n";
	std::wcout << "	file=FILE		Read FILE as the task schema.\n";
	std::wcout << "\n";
	std::wcout << "This program built for i386-pc\n";
	std::wcout << "Report bugs to http://code.google.com/p/pcassist/issues/list\n";
}

bool IsValidOption(const CString& option)
{
	if(sValidOptions.empty())
		InitializeValidOptions();

	for (std::list<CString>::iterator it = sValidOptions.begin(); it != sValidOptions.end(); ++it)
	{
		if(it->CompareNoCase(option) == 0)
			return true;
	}

	return false; // Not find
}

void InitializeValidOptions()
{
	sValidOptions.push_back(_T("-?"));
	sValidOptions.push_back(_T("/?"));
	sValidOptions.push_back(_T("file"));
}

// Append value with separator
void AppendParameterValue(Parameter& para, CString& appendedValue)
{
	CString newValue = para.GetRawdValue();
	if(newValue.IsEmpty())
	{
		newValue = appendedValue;
	}
	else
	{
		newValue.Format(_T("%s %s"), newValue.GetBuffer(), appendedValue.GetBuffer());
	}
	para.SetValue(newValue);	
}
