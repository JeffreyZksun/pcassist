#include "stdafx.h"

#include "Diagnostics.h"

using namespace Ts;
bool gAssertEnabled = true;

void Ts::EnableAssert()
{
	gAssertEnabled = true;
}

void Ts::DisableAssert()
{
	gAssertEnabled = false;
}

bool Ts::IsAssertEnable()
{
	return gAssertEnabled;
}