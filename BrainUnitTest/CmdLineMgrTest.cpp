#include "StdAfx.h"

#include "CmdOption.h"
#include "CmdLineMgr.h"

using namespace Ts;

// Add/get supported options
TEST(CmdLineMgrTest, Test_BeforeParsing)
{
	Ts::CmdLineMgr::pointer pCmdMgr(Ts::CmdLineMgr::Create());

	{
		CmdOptionPtr pOption = pCmdMgr->GetSupportedOptionByName("file");
		EXPECT_EQ(true, NULL == pOption);

		const NString& strUnrec = pCmdMgr->GetUnrecongnizedOption();
		EXPECT_EQ("", strUnrec);
	}

	{
		CmdOptionPtr pOption( new CmdOption("help", "Display help message", CmdOption::eNoValue));
		bool ok = pCmdMgr->AddSupportedOption(pOption);
		EXPECT_EQ(true, ok);


		if(ok)
		{
			ok = pCmdMgr->AddSupportedOption(pOption);
			EXPECT_EQ(false, ok); // Duplicated
		}
	}

	{
		CmdOptionPtr pOption(new CmdOption("file", 'F', "file name"));
		bool ok = pCmdMgr->AddSupportedOption(pOption);

		if(ok)
		{
			ok = pCmdMgr->AddSupportedOption(pOption);
			EXPECT_EQ(false, ok); // Duplicated
		}
	}

	{
		CmdOptionPtr pOption = pCmdMgr->GetSupportedOptionByName("help");

		EXPECT_EQ(true, pOption != NULL);

		if(pOption != NULL)
		{
			const NString& strName = pOption->GetName();
			EXPECT_EQ("help", strName);
			const char strShortName = pOption->GetShortName();
			EXPECT_EQ(0, strShortName);

			const NString& strDesc = pOption->GetDescription();
			EXPECT_EQ("Display help message", strDesc);

			const CmdOption::EValueType eType = pOption->GetValueType();
			EXPECT_EQ(CmdOption::eNoValue, eType);

			const NString& strValue = pOption->GetValue();
			EXPECT_EQ("", strValue);
		}
	}

	{
		CmdOptionPtr pOption = pCmdMgr->GetSupportedOptionByName("file");

		EXPECT_EQ(true, pOption != NULL);
		if(pOption != NULL)
		{
			const NString& strName = pOption->GetName();
			EXPECT_EQ("file", strName);
			const char strShortName = pOption->GetShortName();
			EXPECT_EQ('F', strShortName);

			const NString& strDesc = pOption->GetDescription();
			EXPECT_EQ("file name", strDesc);

			const CmdOption::EValueType eType = pOption->GetValueType();
			EXPECT_EQ(CmdOption::eString, eType);

			const NString& strValue = pOption->GetValue();
			EXPECT_EQ("", strValue);
		}
	}
	{
		const bool bExist = pCmdMgr->HasRecognizedOption();
		EXPECT_EQ(false, bExist);
	}
}

// ExeName -F script.xml --help
TEST(CmdLineMgrTest, Test_AllValidOptions)
{
	char* argv[] = {{"ExeName"}, {"-F"}, {"script.xml"}, {"--help"} };
	int argc = 4;

	Ts::CmdLineMgr::pointer pCmdMgr(Ts::CmdLineMgr::Create());
	{
		CmdOptionPtr pOption(new CmdOption("help", "Display help message", CmdOption::eNoValue));
		bool ok = pCmdMgr->AddSupportedOption(pOption);
	}

	{
		CmdOptionPtr pOption (new CmdOption("file", 'F', "file name"));
		bool ok = pCmdMgr->AddSupportedOption(pOption);
	}

	bool ok = pCmdMgr->Parse(argc, argv);
	EXPECT_EQ(true, ok);

	bool bHasUnrecognaizedOption = pCmdMgr->HasUnrecognizedOption();
	EXPECT_EQ(false, bHasUnrecognaizedOption);

	{
		CmdOptionPtr pOption = pCmdMgr->GetRecognizedOptionByName("help");

		EXPECT_EQ(true, pOption != NULL);

		if(pOption != NULL)
		{
			const NString& strName = pOption->GetName();
			EXPECT_EQ("help", strName);
			const char strShortName = pOption->GetShortName();
			EXPECT_EQ(0, strShortName);

			const NString& strDesc = pOption->GetDescription();
			EXPECT_EQ("Display help message", strDesc);

			const CmdOption::EValueType eType = pOption->GetValueType();
			EXPECT_EQ(CmdOption::eNoValue, eType);

			const NString& strValue = pOption->GetValue();
			EXPECT_EQ("", strValue);
		}
	}

	{
		CmdOptionPtr pOption = pCmdMgr->GetRecognizedOptionByName("file");

		EXPECT_EQ(true, pOption != NULL);
		if(pOption != NULL)
		{
			const NString& strName = pOption->GetName();
			EXPECT_EQ("file", strName);
			const char strShortName = pOption->GetShortName();
			EXPECT_EQ('F', strShortName);

			const NString& strDesc = pOption->GetDescription();
			EXPECT_EQ("file name", strDesc);

			const CmdOption::EValueType eType = pOption->GetValueType();
			EXPECT_EQ(CmdOption::eString, eType);

			const NString& strValue = pOption->GetValue();
			EXPECT_EQ("script.xml", strValue);
		}
	}
}

// ExeName --Tags "tag1 tag2 tag3" --unrecognized "unknwon1 unknown2"
TEST(CmdLineMgrTest, Test_MixValidAndInvalidOptions)
{
	char* argv[] = {{"ExeName"}, {"--Tags"}, {"tag1 tag2 tag3"}, {"--unrecognized"} , {"unknwon1 unknown2"}};
	int argc = 5;

	Ts::CmdLineMgr::pointer pCmdMgr(Ts::CmdLineMgr::Create());
	{
		CmdOptionPtr pOption(new CmdOption("Tags", "Display tags", CmdOption::eString));
		bool ok = pCmdMgr->AddSupportedOption(pOption);
	}

	bool ok = pCmdMgr->Parse(argc, argv);
	EXPECT_EQ(true, ok);

	bool bHasUnrecognaizedOption = pCmdMgr->HasUnrecognizedOption();
	EXPECT_EQ(true, bHasUnrecognaizedOption);

	const NString& strUnrec = pCmdMgr->GetUnrecongnizedOption();
	const NString expected = "--unrecognized \"unknwon1 unknown2\"";
	EXPECT_EQ(expected, strUnrec);

	{
		CmdOptionPtr pOption = pCmdMgr->GetRecognizedOptionByName("Tags");

		EXPECT_EQ(true, pOption != NULL);

		if(pOption != NULL)
		{
			const NString& strName = pOption->GetName();
			EXPECT_EQ("Tags", strName);

			const NString& strValue = pOption->GetValue();
			EXPECT_EQ("tag1 tag2 tag3", strValue);
		}
	}
}

// -F script.xml --help
TEST(CmdLineMgrTest, Test_AllValidStringOptions)
{
	NString strOptions = "-F script.xml --help";

	Ts::CmdLineMgr::pointer pCmdMgr(Ts::CmdLineMgr::Create());
	{
		CmdOptionPtr pOption(new CmdOption("help", "Display help message", CmdOption::eNoValue));
		bool ok = pCmdMgr->AddSupportedOption(pOption);

	}

	{
		CmdOptionPtr pOption (new CmdOption("file", 'F', "file name"));
		bool ok = pCmdMgr->AddSupportedOption(pOption);

	}

	bool ok = pCmdMgr->Parse(strOptions);
	EXPECT_EQ(true, ok);

	bool bHasUnrecognaizedOption = pCmdMgr->HasUnrecognizedOption();
	EXPECT_EQ(false, bHasUnrecognaizedOption);

	{
		CmdOptionPtr pOption = pCmdMgr->GetRecognizedOptionByName("help");

		EXPECT_EQ(true, pOption != NULL);

		if(pOption != NULL)
		{
			const NString& strName = pOption->GetName();
			EXPECT_EQ("help", strName);
			const char strShortName = pOption->GetShortName();
			EXPECT_EQ(0, strShortName);

			const NString& strDesc = pOption->GetDescription();
			EXPECT_EQ("Display help message", strDesc);

			const CmdOption::EValueType eType = pOption->GetValueType();
			EXPECT_EQ(CmdOption::eNoValue, eType);

			const NString& strValue = pOption->GetValue();
			EXPECT_EQ("", strValue);
		}
	}

	{
		CmdOptionPtr pOption = pCmdMgr->GetRecognizedOptionByName("file");

		EXPECT_EQ(true, pOption != NULL);
		if(pOption != NULL)
		{
			const NString& strName = pOption->GetName();
			EXPECT_EQ("file", strName);
			const char strShortName = pOption->GetShortName();
			EXPECT_EQ('F', strShortName);

			const NString& strDesc = pOption->GetDescription();
			EXPECT_EQ("file name", strDesc);

			const CmdOption::EValueType eType = pOption->GetValueType();
			EXPECT_EQ(CmdOption::eString, eType);

			const NString& strValue = pOption->GetValue();
			EXPECT_EQ("script.xml", strValue);
		}
	}

	{
		const bool bExist = pCmdMgr->HasRecognizedOption();
		EXPECT_EQ(true, bExist);
	}
}

// -F script.xml --help
TEST(CmdLineMgrTest, Test_Description)
{
	NString strOptions = "-F script.xml --help";

	Ts::CmdLineMgr::pointer pCmdMgr(Ts::CmdLineMgr::Create());
	{
		CmdOptionPtr pOption (new CmdOption("help", "Display help message", CmdOption::eNoValue));
		const bool ok = pCmdMgr->AddSupportedOption(pOption);
	}

	{
		CmdOptionPtr pOption(new CmdOption("file", 'F', "file name"));
		const bool ok = pCmdMgr->AddSupportedOption(pOption);
	}

	const bool ok = pCmdMgr->Parse(strOptions);
	EXPECT_EQ(true, ok);

	const NString options_Desc = pCmdMgr->GetOptionDescription();
	const NString expectedStr = "Allowed options:\n  --help                Display help message\n  -F [ --file ] arg     file name\n";
	EXPECT_EQ(expectedStr, options_Desc);
}

// -F script.xml --help
TEST(CmdLineMgrTest, Test_UnrecognizedOptions)
{
	NString strOptions = "-T script.xml --help2";

	Ts::CmdLineMgr::pointer pCmdMgr(Ts::CmdLineMgr::Create());
	{
		CmdOptionPtr pOption(new CmdOption("help", "Display help message", CmdOption::eNoValue));
		const bool ok = pCmdMgr->AddSupportedOption(pOption);
	}

	{
		CmdOptionPtr pOption(new CmdOption("file", 'F', "file name"));
		const bool ok = pCmdMgr->AddSupportedOption(pOption);
	}

	const bool ok = pCmdMgr->Parse(strOptions);
	EXPECT_EQ(true, ok);

	const bool bExist = pCmdMgr->HasRecognizedOption();
	EXPECT_EQ(false, bExist);
}