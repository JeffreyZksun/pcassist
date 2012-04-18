#include "stdafx.h"

#include "StringUtil.h"

#include <codecvt>
#include <cstdio>
#include <cstdlib>
#include <cstring>


using namespace Ts;

/************************************************************************/
/*                                                                      */
/************************************************************************/

// http://stackoverflow.com/questions/6140223/c-boost-encode-decode-utf-8
void StringUtil::decode_utf8(const std::string& bytes, std::wstring& wstr)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t> > conv;
	wstr = conv.from_bytes(bytes);
}

void StringUtil::encode_utf8(const std::wstring& wstr, std::string& bytes)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t> > conv;
	bytes = conv.to_bytes(wstr);
}