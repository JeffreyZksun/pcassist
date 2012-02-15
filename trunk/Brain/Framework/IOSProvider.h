#pragma once

// The IOSProvider encapsulates all the changes related to OS, such as the API.

#include <atlstr.h>

class IOSProvider
{
public:
	virtual ~IOSProvider() {}

	virtual CString GetExeModulePath() = 0;
	virtual CString GetUserName() = 0;
	virtual CString GetComputerName() = 0;
	virtual CString GetPlatformString() = 0; // x86 or x64
};
