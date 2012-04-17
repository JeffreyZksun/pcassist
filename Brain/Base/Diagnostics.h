#pragma once
// This file defines all the diagnostic utilities.

// #include <boost/assert.hpp> // It consumes the <assert.h>.
// #include <assert.h> // the assert will abort the program
#include <afxcom_.h> // For ASSERT

namespace Ts
{
	extern void EnableAssert();
	extern void DisableAssert();
	extern inline bool IsAssertEnable();
}

#define DATA_ASSERT(expr) if(Ts::IsAssertEnable()) ASSERT(expr);

