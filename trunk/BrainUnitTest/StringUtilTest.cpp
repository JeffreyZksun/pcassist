#include "StdAfx.h"


#include <StringUtil.h>

using namespace Ts;



TEST(StringUtilTest, EncodeDecode)
{
	std::wstring wstr =		L"abc~!@#$%^&*()_+123456789";
	std::string str =		 "abc~!@#$%^&*()_+123456789";

	{
		std::wstring decode_wstr = StringUtil().convert_to_wstring(str);
		std::string encode_str = StringUtil().convert_to_string(wstr);

		EXPECT_EQ(wstr, decode_wstr);
		EXPECT_EQ(str, encode_str);
	}

	{
		std::wstring decode_wstr;
		std::string encode_str;

		StringUtil util;
		util.decode_utf8(str, decode_wstr);
		util.encode_utf8(wstr, encode_str);

		EXPECT_EQ(wstr, decode_wstr);
		EXPECT_EQ(str, encode_str);
	}
}

TEST(StringUtilTest, Conversion)
{
	CString cstr =						L"abc~!@#$%^&*()_+123456789";
	std::wstring expected_wstr =		L"abc~!@#$%^&*()_+123456789";

	StringUtil util;
	std::wstring converted_wstr = util.convert_to_wstring(cstr);

	EXPECT_EQ(expected_wstr, converted_wstr);
}