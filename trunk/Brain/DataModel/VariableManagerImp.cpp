#include "StdAfx.h"
#include "VariableManagerImp.h"
#include <list>
#include <algorithm>
#include "CloseLoopChecker.h"
#include "XmlIOStream.h"
#include "ConstantsDefinition.h"
#include "Logger.h"
#include "BrainUtil.h" // ToDo remove this reference later.
#include "IOSProvider.h"
#include "BrainApplication.h"
#include "IOSProvider.h"

//////////////////////////////////////////////////////////////////////////
// Dead loop checker
//////////////////////////////////////////////////////////////////////////

static CloseLoopChecker sVariableManagerCloseLoopChecker;

//////////////////////////////////////////////////////////////////////////
// VariableManagerImp
//////////////////////////////////////////////////////////////////////////

VariableManagerImp::VariableManagerImp(VariableManager* pSelf, IOSProvider* pOSProvider) 
	: m_pSelf(pSelf), mUserParameterTable(), mBuiltinParameterTable()
{
	InitializeBuiltInGlobalVariables(pOSProvider);
}

VariableManagerImp::~VariableManagerImp(void)
{
}

 CString VariableManagerImp::GetEvaluatedString(const CString& variableString) const
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

         CString evalStr = para.GetEvaluatedValue(Self());

		 sVariableManagerCloseLoopChecker.Pop();


         varItem.Insert(0, _T('%'));
         varItem.AppendChar(_T('%'));

         evaluatedString.Replace(varItem, evalStr);


         bExist = GetNextVariable(evaluatedString, varItem);
     }

     evaluatedString.Replace(_T("%%"), _T("%")); // Replace the %% to be %

     return evaluatedString;
 }

 void VariableManagerImp::AddUserParameter(const Parameter& para)
 {
	mUserParameterTable.AddParameter(para);
 }

 bool VariableManagerImp::GetParameter(const CString& paraName, Parameter& para) const
 {
	 bool bRet = mUserParameterTable.GetParameter(paraName, para);
	 if(bRet) 
		 return true;

	 bRet = mBuiltinParameterTable.GetParameter(paraName, para);
	 return bRet;
 }

 // GetNextVariable(_T("C:\\temp%%\\%userPath%\\local\\%NextOne%\\readme.txt")); return userPath
 // The return value doesn't include the %.
 bool VariableManagerImp::GetNextVariable(const CString& variableString, CString& varItem) const
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

// ParameterTable& VariableManagerImp::GetParameterTable()
//{
//	return mUserParameterTable;
//}

void VariableManagerImp::AddBuiltinParameter(const Parameter& para)
{
	mBuiltinParameterTable.AddParameter(para);
}

void VariableManagerImp::InitializeBuiltInGlobalVariables(IOSProvider* pOSProvider)
{
	if(pOSProvider)
	{
		{
			// *ExeModulePath
			CString strExePath = pOSProvider->GetExeModulePath();
			Parameter para(EXE_MODULE_PATH, strExePath);
			AddBuiltinParameter(para);

		}
		{
			// *UserName
			CString strUserName = pOSProvider->GetUserName();
			Parameter para(USER_NAME, strUserName);
			AddBuiltinParameter(para);
		}
		{
			// *ComputerName
			CString strComputerName = pOSProvider->GetComputerName();
			Parameter para(COMPUTER_NAME, strComputerName);
			AddBuiltinParameter(para);
		}
		{
			// *Platform
			CString strPlatfrom = pOSProvider->GetPlatformString();
			Parameter para(PLATFORM, strPlatfrom);
			AddBuiltinParameter(para);
		}
	}	
}

VariableManager* VariableManagerImp::Self() const
{
	return m_pSelf;
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

bool VariableManagerImp::XmlIn(XmlIOStream* pXmlIOStream)
{
	ASSERT(pXmlIOStream != NULL);
	{
		XmlIOStreamBeginNodeStack stack(pXmlIOStream, GlobalVariablesNode);
		if(stack.IsSuccess())
			mUserParameterTable.XmlIn(pXmlIOStream);
	}
	return true;
}

bool VariableManagerImp::XmlOut(XmlIOStream* pXmlIOStream) const
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

