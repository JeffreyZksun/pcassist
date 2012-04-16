#pragma once

#include "stdafx.h"
#include "ImmediateTask.h"
#include "ImmediateTaskImp.h"

using namespace Ts;

ImmediateTaskImp::ImmediateTaskImp(owner_pointer pSelf, const WString& taskName)			
	: TaskBaseImp(pSelf, taskName)				
{											
}											

bool ImmediateTaskImp::Execute(ITaskSystem* pTaskSystem)
{
	// Todo
	return false;
}