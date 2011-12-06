#include "StdAfx.h"
#include "CommandLineService.h"

class dummyService: public CommandLineService
{
public:
	virtual void		PrintHelp() {}
	virtual CString		GetVersion() {return _T("123");}
};

// ExeName arg1=first
TEST(CommandLineService, Test_1)
{
	_TCHAR* argv[] = {{_T("ExeName")}, {_T("arg1=first")} };
	int argc = 2;

	dummyService cmdSrv;
	cmdSrv.AddSupportedArgumentName(_T("arg1"));

	cmdSrv.AnalyzeArguments(argc, argv);


	int length = cmdSrv.GetArgementsLength();
	bool bHasInvalidArg = cmdSrv.HasInvalidArguments();

	EXPECT_EQ(1, length);
	EXPECT_EQ(false, bHasInvalidArg);
}

// ExeName arg1=first --list "arg3=the third"
TEST(CommandLineService, Test_2)
{
	_TCHAR* argv[] = {{_T("ExeName")}, {_T("arg1=first")}, {_T("--list")}, {_T("arg3=the third")} };
	int argc = 4;

	dummyService cmdSrv;
	cmdSrv.AddSupportedArgumentName(_T("arg1"));
	cmdSrv.AddSupportedArgumentName(_T("--list"));
	cmdSrv.AddSupportedArgumentName(_T("arg3"));

	cmdSrv.AnalyzeArguments(argc, argv);


	int length = cmdSrv.GetArgementsLength();
	bool bHasInvalidArg = cmdSrv.HasInvalidArguments();

	EXPECT_EQ(3, length);
	EXPECT_EQ(false, bHasInvalidArg);

	{
		const Parameter* pPara = cmdSrv.GetArgument(_T("arg1"));
		CString strExpected = _T("first");

		EXPECT_EQ(true, pPara != NULL);
		if(pPara != NULL)
			EXPECT_EQ(true, strExpected.CompareNoCase(pPara->GetRawValue()) == 0);
	}

	{
		const Parameter* pPara = cmdSrv.GetArgument(_T("--list"));
		CString strExpected = _T("--list");

		EXPECT_EQ(true, pPara != NULL);
		if(pPara != NULL)
			EXPECT_EQ(true, strExpected.CompareNoCase(pPara->GetRawValue()) == 0);
	}

	{
		const Parameter* pPara = cmdSrv.GetArgument(_T("arg3"));
		CString strExpected = _T("the third");

		EXPECT_EQ(true, pPara != NULL);
		if(pPara != NULL)
		{
			int diff = strExpected.CompareNoCase(pPara->GetRawValue());
			bool bEqual = diff == 0;
			EXPECT_EQ(true, bEqual);
		}
	}
}

// ExeName arg1=first --list "arg3=the third"
TEST(CommandLineService, Test_3)
{
	_TCHAR* argv[] = {{_T("ExeName")}, {_T("arg1=first")}, {_T("--list")}, {_T("arg3=the third")} };
	int argc = 4;

	dummyService cmdSrv;
	cmdSrv.AddSupportedArgumentName(_T("arg1"));
	cmdSrv.AddSupportedArgumentName(_T("--list"));

	cmdSrv.AnalyzeArguments(argc, argv);


	int length = cmdSrv.GetArgementsLength();
	bool bHasInvalidArg = cmdSrv.HasInvalidArguments();

	EXPECT_EQ(2, length);

	{
		const Parameter* pPara = cmdSrv.GetArgument(_T("arg1"));
		CString strExpected = _T("first");

		EXPECT_EQ(true, pPara != NULL);
		if(pPara != NULL)
			EXPECT_EQ(true, strExpected.CompareNoCase(pPara->GetRawValue()) == 0);
	}

	{
		const Parameter* pPara = cmdSrv.GetArgument(_T("--list"));
		CString strExpected = _T("--list");

		EXPECT_EQ(true, pPara != NULL);
		if(pPara != NULL)
			EXPECT_EQ(true, strExpected.CompareNoCase(pPara->GetRawValue()) == 0);
	}

	{
		CString strInvalidArg = cmdSrv.GetInvalidArguments();
		CString strExpected = _T("\"arg3=the third\"");

		EXPECT_EQ(true, strExpected.CompareNoCase(strInvalidArg) == 0);
	}
}

// ExeName arg1=first /invalid --list "arg3=the third"
TEST(CommandLineService, Test_4)
{
	_TCHAR* argv[] = {{_T("ExeName")}, {_T("arg1=first")}, {_T("/invalid")}, {_T("--list")}, {_T("arg3=the third")} };
	int argc = 5;

	dummyService cmdSrv;
	cmdSrv.AddSupportedArgumentName(_T("arg1"));
	cmdSrv.AddSupportedArgumentName(_T("--list"));

	cmdSrv.AnalyzeArguments(argc, argv);


	int length = cmdSrv.GetArgementsLength();
	bool bHasInvalidArg = cmdSrv.HasInvalidArguments();

	EXPECT_EQ(2, length);

	{
		const Parameter* pPara = cmdSrv.GetArgument(_T("arg1"));
		CString strExpected = _T("first");

		EXPECT_EQ(true, pPara != NULL);
		if(pPara != NULL)
			EXPECT_EQ(true, strExpected.CompareNoCase(pPara->GetRawValue()) == 0);
	}

	{
		const Parameter* pPara = cmdSrv.GetArgument(_T("--list"));
		CString strExpected = _T("--list");

		EXPECT_EQ(true, pPara != NULL);
		if(pPara != NULL)
			EXPECT_EQ(true, strExpected.CompareNoCase(pPara->GetRawValue()) == 0);
	}

	{
		CString strInvalidArg = cmdSrv.GetInvalidArguments();
		CString strExpected = _T("/invalid \"arg3=the third\"");

		EXPECT_EQ(true, strExpected.CompareNoCase(strInvalidArg) == 0);
	}
}

