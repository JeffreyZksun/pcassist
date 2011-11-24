#include "StdAfx.h"
#include "VariableManager.h"
#include <list>
#include <algorithm>
#include "CloseLoopChecker.h"
#include "XmlIOStream.h"
#include "ConstantsDefinition.h"
#include <lmcons.h> // UNLEN CNLEN
#include "Logger.h"
#include "BrainUtil.h" // ToDo remove this reference later.

//////////////////////////////////////////////////////////////////////////
// Dead loop checker
//////////////////////////////////////////////////////////////////////////

static CloseLoopChecker sVariableManagerCloseLoopChecker;

//////////////////////////////////////////////////////////////////////////
// VariableManager
//////////////////////////////////////////////////////////////////////////

VariableManager::VariableManager(void) : mUserParameterTable(), mBuiltinParameterTable()
{
	InitializeBuiltInGlobalVariables();
}

VariableManager::~VariableManager(void)
{
}

 CString VariableManager::GetEvaluatedString(const CString& variableString) const
 {
     CString evaluatedString = variableString;

     CString varItem;
     Parameter para;

     bool bExist = GetNextVariable(evaluatedString, varItem);

     while(bExist) // Parse the variable one by one.
     {
         bool bRet = GetParameter(varItem, para);
         if(!bRet) // No this variable
             break;

		 // Detect dead loop caused by the close loop reference. Such as (ExePath, %AppPath%/bin) (AppPath, %ExePath%/../)
		 if(!sVariableManagerCloseLoopChecker.PushOngoingItem(varItem))
		 {
			 ASSERT(!_T("Error: Parameter evalation loop is detected"));
			 LogOut(_T("Error: Parameter evalation loop is detected=> "), COLOR_RED);
			 LogOut(varItem, COLOR_RED);
			 LogOut(_T("\n"), COLOR_RED);

			// Return empty string. Can't return para.GetRawValue() here,
			 // otherwise the variable in the raw value will be evaluated again.
			 return _T("");  
		 }

         CString evalStr = para.GetEvaluatedValue();

		 sVariableManagerCloseLoopChecker.Pop();


         varItem.Insert(0, _T('%'));
         varItem.AppendChar(_T('%'));

         evaluatedString.Replace(varItem, evalStr);


         bExist = GetNextVariable(evaluatedString, varItem);
     }

     evaluatedString.Replace(_T("%%"), _T("%")); // Replace the %% to be %

     return evaluatedString;
 }

 void VariableManager::AddUserParameter(const Parameter& para)
 {
	mUserParameterTable.AddParameter(para);
 }

 bool VariableManager::GetParameter(const CString& paraName, Parameter& para) const
 {
	 bool bRet = mUserParameterTable.GetParameter(paraName, para);
	 if(bRet) 
		 return true;

	 bRet = mBuiltinParameterTable.GetParameter(paraName, para);
	 return bRet;
 }

 // GetNextVariable(_T("C:\\temp%%\\%userPath%\\local\\%NextOne%\\readme.txt")); return userPath
 // The return value doesn't include the %.
 bool VariableManager::GetNextVariable(const CString& variableString, CString& varItem) const
 {
     int posStart = variableString.Find(_T('%'));
     if(-1 == posStart)
         return false; // not found

     // skip all the "%%"
     WCHAR nextChar = variableString.GetAt(posStart + 1);
     while(_T('%') == nextChar) // find "%%", skip them
     {
         posStart += 2;

         posStart = variableString.Find(_T('%'), posStart);
         if(-1 == posStart)
             return false; // not found

         nextChar = variableString.GetAt(posStart + 1);
     }

     int posEnd = variableString.Find(_T('%'), posStart + 1);
     if(-1 == posEnd)
         return false; // not found

     varItem = variableString.Left(posEnd);
     varItem = varItem.Right(posEnd - posStart - 1);

     return true;
 }

// ParameterTable& VariableManager::GetParameterTable()
//{
//	return mUserParameterTable;
//}

void VariableManager::AddBuiltinParameter(const Parameter& para)
{
	mBuiltinParameterTable.AddParameter(para);
}

void VariableManager::InitializeBuiltInGlobalVariables()
{
	// ToDo - Don't save the built in variables.
	{
		// *ExeModulePath
		TCHAR exeName[MAX_PATH];
		if (GetModuleFileName(NULL, exeName, MAX_PATH) != 0)
		{
			CString strExeName = exeName; // such as C:\Program file\PC.exe
			int pos = strExeName.ReverseFind(_T('\\'));
			CString strExePath = strExeName.Left(pos);
			Parameter para(EXE_MODULE_PATH, strExePath);
			AddBuiltinParameter(para);
		}
	}
	{
		// *UserName
		DWORD unMaxLength = UNLEN + 1;
		TCHAR userName [ UNLEN + 1 ];

		CString strUserName;
		if (::GetUserName( (TCHAR*)userName, &unMaxLength ))
			strUserName = userName;
		else
			strUserName = _T("UnknownUserName");

		Parameter para(USER_NAME, strUserName);
		AddBuiltinParameter(para);
	}
	{
		// *ComputerName
		DWORD cnMaxLenggh = CNLEN + 1;
		TCHAR computerName[CNLEN + 1];
		CString strComputerName;
		if(::GetComputerName(computerName, &cnMaxLenggh))
			strComputerName = computerName;
		else
			strComputerName = _T("UnknownComputerName");

		Parameter para(COMPUTER_NAME, strComputerName);
		AddBuiltinParameter(para);
	}
    {
        // *Platform
        CString folderName = _T("C:\\Program Files (x86)");

        bool bIsx64 = BrainUtil::DoesFileorFolderExist(folderName);
        CString strPlatfrom = _T("x86");
        if(bIsx64)
            strPlatfrom = _T("x64");

        Parameter para(PLATFORM, strPlatfrom);
        AddBuiltinParameter(para);
    }
}
 
/************************************************************************
 The data format is:
 
 <GlobalVariables>
	<Parameter> ...</Parameter>
	<Parameter>...</Parameter>
	<Parameter>...</Parameter>
	...
 </GlobalVariables>
************************************************************************/
#define GlobalVariablesNode _T("GlobalVariables")

bool VariableManager::XmlIn(XmlIOStream* pXmlIOStream)
{
	ASSERT(pXmlIOStream != NULL);
	{
		XmlIOStreamBeginNodeStack stack(pXmlIOStream, GlobalVariablesNode);
		if(stack.IsSuccess())
			mUserParameterTable.XmlIn(pXmlIOStream);
	}
	return true;
}

bool VariableManager::XmlOut(XmlIOStream* pXmlIOStream) const
{
	ASSERT(pXmlIOStream != NULL);	

	{
		XmlIOStreamBeginNodeStack stack(pXmlIOStream, GlobalVariablesNode);
		ASSERT(stack.IsSuccess());
		if(!stack.IsSuccess())
			return false;
		mUserParameterTable.XmlOut(pXmlIOStream);
	}

	return true;
}

