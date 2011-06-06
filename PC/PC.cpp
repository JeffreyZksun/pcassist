// PC.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <list>

#include "DocumentManager.h"
#include "TaskManager.h"

// Define the supported parameter names.
#define XMLFILE _T("File")

// The command line likes PC.exe File="C:\Tools\_RunAutomation.xml"
int _tmain(int argc, _TCHAR* argv[])
{
	ParameterObject parameters;
	// The first parameter is the command name itself.
	bool hasLocalISFolder = false;
	bool hasISVersion = false;
	CString str;
	for(int i = 1; i < argc; i++)
	{
		// Find the assignment operator "="
		str = argv[i];
		int pos = str.Find(_T('='));
		if (-1 == pos) // not find
			continue;

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
		parameters.AddParameter(varPara);
	}

	Parameter xmlFileName;
	bool bRet = parameters.GetParameter(XMLFILE, xmlFileName);
	ASSERT(bRet);
	if(!bRet)
	{
		return 1;
	}

	DocumentManager* pDoc = new DocumentManager();
	pDoc->SetDocumentName(xmlFileName.GetEvaluatedValue());
	pDoc->XmlIn();
	TaskManager::Get()->RunTasks();
	delete pDoc;

	return 0;
}

