#pragma once

#pragma once


class RegistryKey 
{
public:
	RegistryKey(void);
	RegistryKey(HKEY hKey, LPCTSTR lpSubKey = NULL);
	~RegistryKey(void);

public:
	//BOOL Create(HKEY hKey, LPCTSTR lpSubKey = NULL);

	BOOL CreateEx(HKEY hKey, LPCTSTR lpSubKey, LPTSTR lpClass = NULL
		, DWORD dwOptions = REG_OPTION_NON_VOLATILE
		, REGSAM samDesired = KEY_ALL_ACCESS
		, LPSECURITY_ATTRIBUTES lpSecurityAttributes = NULL
		, LPDWORD lpdwDisposition = NULL);

	BOOL OpenEx(HKEY hKey, LPCTSTR lpSubKey, REGSAM samDesired = KEY_ALL_ACCESS);

	LONG QueryValueEx(LPCTSTR lpValueName, LPDWORD lpType, LPBYTE lpData, LPDWORD lpcbData) const;

	LONG SetValueEx(LPCTSTR lpValueName, DWORD dwType, const BYTE* lpData, DWORD cbData);

	LONG QueryValueSize(LPCTSTR lpValueName, LPDWORD lpcbData, LPDWORD lpType = NULL) const;

	BOOL QueryValue(LPCTSTR lpValueName, DWORD &dwValue) const;

	BOOL QueryValue(LPCTSTR lpValueName, bool &bValue) const;

	BOOL QueryValue(LPCTSTR lpValueName, LONGLONG &llValue) const;
	BOOL QueryValue(LPCSTR lpValueName, CStringA &sValue) const;

	BOOL QueryValue(LPCWSTR lpValueName, CStringW &sValue) const;

	BOOL QueryValue(LPCOLESTR lpValueName, CComBSTR &bsValue) const;

	LONG SetValue(LPCTSTR lpValueName, const CStringA &sValue);

	LONG SetValue(LPCOLESTR lpValueName, const CStringW &wsValue);

	LONG SetValue(LPCOLESTR lpValueName, BSTR bsValue);

	LONG SetValue(LPCTSTR lpValueName, DWORD dwValue);

	LONG SetValue(LPCTSTR lpValueName, bool bValue);

	LONG SetValue(LPCTSTR lpValueName, LONGLONG llValue);

	LONG DeleteValue(LPCSTR lpValueName);

	LONG DeleteValue(LPCOLESTR lpValueName);

	DWORD DeleteKey(LPCTSTR lpSubKey);

	LONG EnumValue(DWORD dwIndex, LPTSTR lpValueName, LPDWORD lpcValueName
		, LPDWORD lpType, LPBYTE lpData, LPDWORD lpcbData);

	BOOL IsKeyEmpty() const;

	BOOL IsValueSet(LPCTSTR lpValueName) const;


private:
	void Attach(HKEY h);
	HKEY Detach();
	BOOL IsValid() const;
	void Close();

public:
	HKEY mhKey;

};

