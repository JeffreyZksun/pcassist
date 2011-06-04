#include "StdAfx.h"
#include "VariableManager.h"
#include <list>
#include <algorithm>

//////////////////////////////////////////////////////////////////////////
// VariableManager
//////////////////////////////////////////////////////////////////////////

static std::list<CString> sEvaluatingParaList;
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
     // ToDo - 

     CString evaluatedString = variableString;

     CString varItem;
     Parameter para;

     bool bExist = GetNextVariable(evaluatedString, varItem);

     while(bExist) // Parse the variable one by one.
     {
         // Detect dead loop caused by the close loop reference. Such as (ExePath, %AppPath%/bin) (AppPath, %ExePath%/../)
         std::list<CString>::iterator it = std::find(sEvaluatingParaList.begin(), sEvaluatingParaList.end(), varItem);
         if(it != sEvaluatingParaList.end())
         {
             // This variable is already in the evaluation stack. 
             // Close  loop reference is detected.
             // Return directly to avoid dead loop.
             ASSERT(!_T("Close loop reference is detected during evaluation."));

             return _T("");  // Return empty string
         }
         else
             sEvaluatingParaList.push_back(varItem);

         bool bRet = GetParameter(varItem, para);
         if(!bRet) // No this variable
             break;

         CString evalStr = para.GetEvaluatedValue();
         varItem.Insert(0, _T('%'));
         varItem.AppendChar(_T('%'));

         evaluatedString.Replace(varItem, evalStr);

         sEvaluatingParaList.pop_back();

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
