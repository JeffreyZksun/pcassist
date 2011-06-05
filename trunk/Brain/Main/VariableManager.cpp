#include "StdAfx.h"
#include "VariableManager.h"
#include <list>
#include <algorithm>
#include "CloseLoopChecker.h"
#include "XmlIOStream.h"

//////////////////////////////////////////////////////////////////////////
// Dead loop checker
//////////////////////////////////////////////////////////////////////////

CloseLoopChecker sVariableManagerCloseLoopChecker;

//////////////////////////////////////////////////////////////////////////
// VariableManager
//////////////////////////////////////////////////////////////////////////

VariableManager::VariableManager(void)
{
}

VariableManager::~VariableManager(void)
{
}

VariableManager* VariableManager::Get()
{
    static VariableManager singleton;
    return &singleton;
}

 CString VariableManager::GetEvaluatedString(const CString& variableString) const
 {
     CString evaluatedString = variableString;

     CString varItem;
     Parameter para;

     bool bExist = GetNextVariable(evaluatedString, varItem);

     while(bExist) // Parse the variable one by one.
     {
		 // Detect dead loop caused by the close loop reference. Such as (ExePath, %AppPath%/bin) (AppPath, %ExePath%/../)
		 if(!sVariableManagerCloseLoopChecker.PushOngoingItem(varItem))
		 {
			 // This variable is already in the evaluation stack. 
			 // Close  loop reference is detected.
			 // Return directly to avoid dead loop.
			 ASSERT(!_T("Close loop reference is detected during evaluation."));

			 return _T("");  // Return empty string
		 }

         bool bRet = GetParameter(varItem, para);
         if(!bRet) // No this variable
             break;

         CString evalStr = para.GetEvaluatedValue();
         varItem.Insert(0, _T('%'));
         varItem.AppendChar(_T('%'));

         evaluatedString.Replace(varItem, evalStr);

         sVariableManagerCloseLoopChecker.Pop();

         bExist = GetNextVariable(evaluatedString, varItem);
     }

     evaluatedString.Replace(_T("%%"), _T("%")); // Replace the %% to be %

     return evaluatedString;
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
 
/************************************************************************
 The data format is:
 
 <GlobalVariables>
	<Parameter> ...</Parameter>
	<Parameter>...</Parameter>
	<Parameter>...</Parameter>
	...
 </GlobalVariables>
************************************************************************/
bool VariableManager::XmlIn(XmlIOStream* pXmlIOStream)
{
	ASSERT(pXmlIOStream != NULL);
	return true;
}

bool VariableManager::XmlOut(XmlIOStream* pXmlIOStream) const
{
	ASSERT(pXmlIOStream != NULL);	

	{
		XmlIOStreamBeginNodeStack stack(pXmlIOStream, _T("GlobalVariables"));
		ParameterObject::XmlOut(pXmlIOStream);
	}

	return true;
}

