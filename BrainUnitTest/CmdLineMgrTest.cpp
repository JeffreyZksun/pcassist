#include "StdAfx.h"

#include "CmdOption.h"
#include "CmdLineMgr.h"

using namespace Ts;

// ExeName -F script.xml --help
TEST(CmdLineMgrTest, Test_1)
{
	char* argv[] = {{"ExeName"}, {"-F"}, {"script.xml"}, {" --help"} };
	int argc = 4;

	Ts::CmdLineMgr cmdMgr;
	{
		CmdOption* pOption = new CmdOption("help", "Display help message");
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
		CmdOption* pHelp = cmdMgr.GetRecognizedOptionByName("help");

		EXPECT_EQ(true, pHelp != NULL);
	}

}
