#pragma once


namespace Ts
{
	class BRAINEXPORT StringUtil
	{
	public:
		void decode_utf8(const std::string& bytes, std::wstring& wstr);
		void encode_utf8(const std::wstring& wstr, std::string& bytes);

		std::wstring convert_to_wstring(const std::string& bytes);
		std::string convert_to_string(const std::wstring& wstr);

		std::wstring convert_to_wstring(const CString& str);
	};
}


