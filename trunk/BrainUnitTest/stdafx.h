// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>


#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // some CString constructors will be explicit

#include <atlbase.h>
#include <atlstr.h>

// : reference additional headers your program requires here
//#include <assert.h> // the assert will abort the program
#include <afxcom_.h> // For ASSERT
#include <gtest/gtest.h>
#include <iostream>

#include "ApplicationSwitchHelper.h"

#include "BrainApplication.h"
#include "TaskManager.h"
#include "BehaviorBodyFactory.h"
#include "VariableManager.h"
#include "DocumentManager.h"
#include "Actions.h"
#include "Conditions.h"