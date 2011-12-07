#include "StdAfx.h"
#include "CommandLineService.h"
#include <algorithm>

CommandLineService::CommandLineService(void)
{
}

CommandLineService::~CommandLineService(void)
{
}

void CommandLineService::AddSupportedArgumentName(const CString& name)
{
	CString tmpName = name;
	tmpName.MakeLower();

	mSupportedArgumentNames.push_back(tmpName);
}

void CommandLineService::AnalyzeArguments(int argc, _TCHAR* argv[])
{
	CString str;
	for(int i = 1; i < argc; i++)
	{
		// Find the assignment operator "="
		str = argv[i];
		int pos = str.Find(_T('='));
		bool bIsAssignmentArgument = pos != -1;
		if (bIsAssignmentArgument) 
		{
			// Verify name is not empty
			CString varName = str.Left(pos);
			if(varName.IsEmpty())
			{
				AddInvalidArguments(str);
				continue;
			}

			CString varValue = str.Right(str.GetLength() - pos - 1);

			if(IsSupportedArgumentName(varName))
				AddSupportedArgumentPair(varName, varValue);	
			else
			{
				AddInvalidArguments(str);
				AddUnsupportedArgumentPair(varName, varValue);
			}
		}
		else // not find
		{
			if(IsSupportedArgumentName(str))
				AddSupportedArgumentPair(str, str);	
			else
			{
				AddInvalidArguments(str);
				AddUnsupportedArgumentPair(str, str);
			}
		}
	}
}

const Parameter* CommandLineService::GetArgument(const CString& argName) const
{
	const Parameter* pResult = NULL;
	pResult = mSupportedArguments.GetParameter(argName);

	return pResult;
}

bool CommandLineService::HasInvalidArguments() const
{
	return (mInvalidArugments.GetLength() != 0);
}

CString	CommandLineService::GetInvalidArguments() const
{
	return mInvalidArugments;
}

unsigned int CommandLineService::GetArgementsLength() const
{
	return mSupportedArguments.GetParameterLength();
}

bool CommandLineService::IsSupportedArgumentName(const CString& name) const
{
	for (std::list<CString>::const_iterator it = mSupportedArgumentNames.begin(); it != mSupportedArgumentNames.end(); ++it)
	{
		if(it->CompareNoCase(name) == 0)
			return true;
	}

	return false; // Not find
}

void CommandLineService::AddSupportedArgumentPair(const CString& name, const CString& val)
{
	Parameter para(name, val);
	mSupportedArguments.AddParameter(para);
}

void CommandLineService::AddUnsupportedArgumentPair(const CString& name, const CString& val)
{
	Parameter para(name, val);
	mUnsupportedArguments.AddParameter(para);
}

void CommandLineService::AddInvalidArguments(const CString& arg)
{
	if(mInvalidArugments.GetLength() != 0)
		mInvalidArugments.Append(_T(" "));

	bool bHasSpace = (arg.Find(_T(" ")) != -1);
	if(bHasSpace)
		mInvalidArugments.Append(_T("\""));

	mInvalidArugments.Append(arg);

	if(bHasSpace)
		mInvalidArugments.Append(_T("\""));
}