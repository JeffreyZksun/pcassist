// PC.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <list>
#include <algorithm>

#include "BrainApplication.h"
#include "TaskManager.h"
#include "Logger.h"

// We need to include the static lib and all the obj files contain the global objects. (Action.obj Condition.obj)
// If only include the static lib, the global objects won't be initialized.
// This results in the actions and conditions can't register themselves.
// http://social.msdn.microsoft.com/Forums/en/vclanguage/thread/5c5ee89d-2a38-483d-8550-484550901170

void AnalyzeInputOptions(int argc, _TCHAR* argv[], ParameterTable& options);
void PrintHelp();
bool IsValidOption(const CString& option);
void InitializeValidOptions();
void AppendParameterValue(Parameter& para, CString& appendedValue);

// define the valid options
static std::list<CString> sValidOptions;

#define PC_VERSION _T("(v1.7)")

// Define the supported parameter names.
#define INVALID_OPTS _T("InvalidOptions") // Collect the invalid options
#define OPT_FILE _T("file") // Read FILE as the task schema.
#define OPT_HELP _T("help")
#define OPT_SHOW_PARAMETER _T("show-parameters")

// The command line likes PC File="C:\_DemoPcUsage.xml"
int _tmain(int argc, _TCHAR* argv[])
{
	ParameterTable options;

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
			prompt.Format(_T("PC: invalid options %s\n"), para.GetRawValue());
			LogOut(prompt);
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

	{
		Parameter para;
		bRet = options.GetParameter(OPT_SHOW_PARAMETER, para);
		bool bOutput = false;
		if(bRet)
		{
			if(para.GetRawValue().CompareNoCase(_T("true")) == 0)
				bOutput = true;
			else
				bOutput = false;
		}

		Logger::Get()->SetDoesOutputParameter(bOutput);
	}


	//DocumentManager* pDoc = new DocumentManager();
	//pDoc->SetDocumentName(fileName.GetEvaluatedValue());
	//bRet = pDoc->XmlIn();
	bRet = BrainApplication::GetWorkingBrain()->XmlIn(fileName.GetEvaluatedValue());

	if(bRet)
		BrainApplication::GetWorkingBrain()->GetTaskManager()->RunTasks();
	else
	{
		LogOut(_T("Can't open file: "), COLOR_RED);
		LogOut(fileName.GetEvaluatedValue(), COLOR_RED);
		LogOut(_T("\n"));
	}

	//delete pDoc;

	return 0;
}

void AnalyzeInputOptions(int argc, _TCHAR* argv[], ParameterTable& options)
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
			if (IsValidOption(str))
			{
				// Check if it's help;
				if(str.CompareNoCase(_T("/?")) == 0 || str.CompareNoCase(_T("-?")) == 0)
					options.AddParameter(Parameter(OPT_HELP, _T("")));
				else
					options.AddParameter(Parameter(str, str));
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

	if(!invalidOptions.GetRawValue().IsEmpty())
		options.AddParameter(invalidOptions);
}

void PrintHelp()
{
	LogOut(_T("Usage: PC [options...]\n"));
	LogOut(_T("Options:\n"));
	LogOut(_T("   -?, /?          Show help.\n"));
	LogOut(_T("   file=FILE       Read FILE as the task schema.\n"));
	LogOut(_T("   show-parameters=true/false  Enable/disable to show the parameters during executing the tasks.\n"));
	LogOut(_T("\n"));
	LogOut(_T("This program built for i386-pc. "));
	LogOut(PC_VERSION);
	LogOut(_T("\n"));
	LogOut(_T("Report bugs to http://code.google.com/p/pcassist/issues/list\n"));
}

void InitializeValidOptions()
{
	sValidOptions.push_back(_T("-?"));
	sValidOptions.push_back(_T("/?"));
	sValidOptions.push_back(OPT_FILE);
	sValidOptions.push_back(OPT_SHOW_PARAMETER);
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

// Append value with separator
void AppendParameterValue(Parameter& para, CString& appendedValue)
{
	CString newValue = para.GetRawValue();
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
