#include "StdAfx.h"

#include "CmdOption.h"


using namespace Ts;

// -F script.xml
TEST(CmdOptionTest, Test_1)
{
	CmdOption* pOption = new CmdOption("file", 'F', "file name");

	const NString& strName = pOption->GetName();
	EXPECT_EQ("file", strName);
	const char strShortName = pOption->GetShortName();
	EXPECT_EQ('F', strShortName);

	const NString strLongAndShortName = pOption->GetLongAndShortName();
	EXPECT_EQ("file,F", strLongAndShortName);

	const NString& strDesc = pOption->GetDescription();
	EXPECT_EQ("file name", strDesc);

	const CmdOption::EValueType eType = pOption->GetValueType();
	EXPECT_EQ(CmdOption::eString, eType);

	const NString& strValue = pOption->GetValue();
	EXPECT_EQ("", strValue);

	delete pOption;
}

// --help
TEST(CmdOptionTest, Test_2)
{
	CmdOption* pOption = new CmdOption("help", "Display help message", CmdOption::eNoValue);

	const NString& strName = pOption->GetName();
	EXPECT_EQ("help", strName);
	const char strShortName = pOption->GetShortName();
	EXPECT_EQ(0, strShortName);
	const NString strLongAndShortName = pOption->GetLongAndShortName();
	EXPECT_EQ("help", strLongAndShortName);

	const NString& strDesc = pOption->GetDescription();
	EXPECT_EQ("Display help message", strDesc);

	const CmdOption::EValueType eType = pOption->GetValueType();
	EXPECT_EQ(CmdOption::eNoValue, eType);

	const NString& strValue = pOption->GetValue();
	EXPECT_EQ("", strValue);

	delete pOption;
}

// -F script.xml
TEST(CmdOptionTest, Test_3)
{
	CmdOption* pOption = new CmdOption("file", 'F', "file name", CmdOption::eString);

	pOption->SetName("fileEx");
	const NString& strName = pOption->GetName();
	EXPECT_EQ("fileEx", strName);
	pOption->SetShortName('X');
	const char strShortName = pOption->GetShortName();
	EXPECT_EQ('X', strShortName);

	const NString strLongAndShortName = pOption->GetLongAndShortName();
	EXPECT_EQ("fileEx,X", strLongAndShortName);

	pOption->SetDescription("file name Ex");
	const NString& strDesc = pOption->GetDescription();
	EXPECT_EQ("file name Ex", strDesc);

	pOption->SetValueType(CmdOption::eNoValue);
	const CmdOption::EValueType eType = pOption->GetValueType();
	EXPECT_EQ(CmdOption::eNoValue, eType);

	pOption->SetValue("script.xml");
	const NString& strValue = pOption->GetValue();
	EXPECT_EQ("script.xml", strValue);

	delete pOption;
}
