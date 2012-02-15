#pragma once

#ifdef _WINOS

#include "IOSProvider.h"

class WindowsProvider : public IOSProvider
{
public:
	virtual ~WindowsProvider();

	virtual CString GetExeModulePath();
	virtual CString GetUserName();
	virtual CString GetComputerName();
	virtual CString GetPlatformString(); // x86 or x64
	
};
#endif // _WINOS
