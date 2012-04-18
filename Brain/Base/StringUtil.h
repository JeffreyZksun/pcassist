#pragma once


namespace Ts
{
	class BRAINEXPORT StringUtil
	{
	public:
		void decode_utf8(const std::string& bytes, std::wstring& wstr);
		void encode_utf8(const std::wstring& wstr, std::string& bytes);
	};
}


