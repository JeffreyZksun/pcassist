#pragma once
// This file defines all the diagnostic utilities.

#include <boost/assert.hpp>

namespace Ts
{
	extern void EnableAssert();
	extern void DisableAssert();
	extern inline bool IsAssertEnable();

}

#define DATA_ASSERT(expr) if(Ts::IsAssertEnable())BOOST_ASSERT(expr);
#define DATA_VERIFY(expr) BOOST_VERIFY(expr);
