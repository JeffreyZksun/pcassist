#pragma once
#include "ParameterTable.h"

// This class contains the common utility to handle the command line arguments
// theExe arg1=xxx "arg2=xx xxx" -xxx 

class CommandLineService
{
public:
	CommandLineService(void);
	virtual ~CommandLineService(void);

public:
	void				AddSupportedArgumentName(const CString& name);
	void				AnalyzeArguments(int argc, _TCHAR* argv[]);

	const Parameter*	GetArgument(const CString& argName) const;

	bool				HasInvalidArguments() const;
	CString				GetInvalidArguments() const;

	unsigned int		GetArgementsLength() const;
public:
	virtual void		PrintHelp() = 0;
	virtual CString		GetVersion() = 0;

private:
	bool				IsSupportedArgumentName(const CString& name) const;
	void				AddSupportedArgumentPair(const CString& name, const CString& val);
	void				AddUnsupportedArgumentPair(const CString& name, const CString& val);
	void				AddInvalidArguments(const CString& arg);

private:
	ParameterTable		mSupportedArguments;

	ParameterTable		mUnsupportedArguments;
	CString				mInvalidArugments;

	std::list<CString>	mSupportedArgumentNames;
};
