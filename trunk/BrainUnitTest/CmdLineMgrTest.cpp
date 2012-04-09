#include "StdAfx.h"

#include "CmdOption.h"
#include "CmdLineMgr.h"

using namespace Ts;

// Add/get supported options
TEST(CmdLineMgrTest, Test_BeforeParsing)
{
	Ts::CmdLineMgr cmdMgr;

	{
		CmdOption* pOption = cmdMgr.GetSupportedOptionByName("file");
		EXPECT_EQ(true, NULL == pOption);

		const NString& strUnrec = cmdMgr.GetUnrecongnizedOption();
		EXPECT_EQ("", strUnrec);
	}

	{
		CmdOption* pOption = new CmdOption("help", "Display help message", CmdOption::eNoValue);
		bool ok = cmdMgr.AddSupportedOption(pOption);
		EXPECT_EQ(true, ok);
		if(!ok)
			delete pOption;

		if(ok)
		{
			ok = cmdMgr.AddSupportedOption(pOption);
			EXPECT_EQ(false, ok); // Duplicated
		}
	}

	{
		CmdOption* pOption = new CmdOption("file", 'F', "file name");
		bool ok = cmdMgr.AddSupportedOption(pOption);
		if(!ok)
			delete pOption;

		if(ok)
		{
			ok = cmdMgr.AddSupportedOption(pOption);
			EXPECT_EQ(false, ok); // Duplicated
		}
	}

	{
		CmdOption* pOption = cmdMgr.GetSupportedOptionByName("help");

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
		CmdOption* pOption = cmdMgr.GetSupportedOptionByName("file");

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
		const bool bExist = cmdMgr.HasRecognizedOption();
		EXPECT_EQ(false, bExist);
	}
}

// ExeName -F script.xml --help
TEST(CmdLineMgrTest, Test_AllValidOptions)
{
	char* argv[] = {{"ExeName"}, {"-F"}, {"script.xml"}, {"--help"} };
	int argc = 4;

	Ts::CmdLineMgr cmdMgr;
	{
		CmdOption* pOption = new CmdOption("help", "Display help message", CmdOption::eNoValue);
		bool ok = cmdMgr.AddSupportedOption(pOption);
		if(!ok)
			delete pOption;
	}

	{
		CmdOption* pOption = new CmdOption("file", 'F', "file name");
		bool ok = cmdMgr.AddSupportedOption(pOption);
		if(!ok)
			delete pOption;
	}

	bool ok = cmdMgr.Parse(argc, argv);
	EXPECT_EQ(true, ok);

	bool bHasUnrecognaizedOption = cmdMgr.HasUnrecognizedOption();
	EXPECT_EQ(false, bHasUnrecognaizedOption);

	{
		CmdOption* pOption = cmdMgr.GetRecognizedOptionByName("help");

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
		CmdOption* pOption = cmdMgr.GetRecognizedOptionByName("file");

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

	Ts::CmdLineMgr cmdMgr;
	{
		CmdOption* pOption = new CmdOption("Tags", "Display tags", CmdOption::eString);
		bool ok = cmdMgr.AddSupportedOption(pOption);
		if(!ok)
			delete pOption;
	}

	bool ok = cmdMgr.Parse(argc, argv);
	EXPECT_EQ(true, ok);

	bool bHasUnrecognaizedOption = cmdMgr.HasUnrecognizedOption();
	EXPECT_EQ(true, bHasUnrecognaizedOption);

	const NString& strUnrec = cmdMgr.GetUnrecongnizedOption();
	const NString expected = "--unrecognized \"unknwon1 unknown2\"";
	EXPECT_EQ(expected, strUnrec);

	{
		CmdOption* pOption = cmdMgr.GetRecognizedOptionByName("Tags");

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

	Ts::CmdLineMgr cmdMgr;
	{
		CmdOption* pOption = new CmdOption("help", "Display help message", CmdOption::eNoValue);
		bool ok = cmdMgr.AddSupportedOption(pOption);
		if(!ok)
			delete pOption;
	}

	{
		CmdOption* pOption = new CmdOption("file", 'F', "file name");
		bool ok = cmdMgr.AddSupportedOption(pOption);
		if(!ok)
			delete pOption;
	}

	bool ok = cmdMgr.Parse(strOptions);
	EXPECT_EQ(true, ok);

	bool bHasUnrecognaizedOption = cmdMgr.HasUnrecognizedOption();
	EXPECT_EQ(false, bHasUnrecognaizedOption);

	{
		CmdOption* pOption = cmdMgr.GetRecognizedOptionByName("help");

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
		CmdOption* pOption = cmdMgr.GetRecognizedOptionByName("file");

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
		const bool bExist = cmdMgr.HasRecognizedOption();
		EXPECT_EQ(true, bExist);
	}
}

// -F script.xml --help
TEST(CmdLineMgrTest, Test_Description)
{
	NString strOptions = "-F script.xml --help";

	Ts::CmdLineMgr cmdMgr;
	{
		CmdOption* pOption = new CmdOption("help", "Display help message", CmdOption::eNoValue);
		const bool ok = cmdMgr.AddSupportedOption(pOption);
		if(!ok)
			delete pOption;
	}

	{
		CmdOption* pOption = new CmdOption("file", 'F', "file name");
		const bool ok = cmdMgr.AddSupportedOption(pOption);
		if(!ok)
			delete pOption;
	}

	const bool ok = cmdMgr.Parse(strOptions);
	EXPECT_EQ(true, ok);

	const NString options_Desc = cmdMgr.GetOptionDescription();
	const NString expectedStr = "Allowed options:\n  --help                Display help message\n  -F [ --file ] arg     file name\n";
	EXPECT_EQ(expectedStr, options_Desc);
}

// -F script.xml --help
TEST(CmdLineMgrTest, Test_UnrecognizedOptions)
{
	NString strOptions = "-T script.xml --help2";

	Ts::CmdLineMgr cmdMgr;
	{
		CmdOption* pOption = new CmdOption("help", "Display help message", CmdOption::eNoValue);
		const bool ok = cmdMgr.AddSupportedOption(pOption);
		if(!ok)
			delete pOption;
	}

	{
		CmdOption* pOption = new CmdOption("file", 'F', "file name");
		const bool ok = cmdMgr.AddSupportedOption(pOption);
		if(!ok)
			delete pOption;
	}

	const bool ok = cmdMgr.Parse(strOptions);
	EXPECT_EQ(true, ok);

	const bool bExist = cmdMgr.HasRecognizedOption();
	EXPECT_EQ(false, bExist);
}