#include "StdAfx.h"


#include <StringUtil.h>

using namespace Ts;



TEST(StringUtilTest, EncodeDecode)
{
	std::wstring wstr =		L"abc~!@#$%^&*()_+123456789";
	std::string str =		 "abc~!@#$%^&*()_+123456789";

	std::wstring decode_wstr;
	std::string encode_str;

	StringUtil util;
	util.decode_utf8(str, decode_wstr);
	util.encode_utf8(wstr, encode_str);

	EXPECT_EQ(wstr, decode_wstr);
	EXPECT_EQ(str, encode_str);
}