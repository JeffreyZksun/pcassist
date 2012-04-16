#pragma once

#include "stdafx.h"

#include "ImmediateTask.h"
#include "ImmediateTaskImp.h"

using namespace Ts;


ImmediateTask::ImmediateTask() 					
{											
}											

ImmediateTask::~ImmediateTask()
{

}

ImmediateTask::pointer ImmediateTask::Create(const WString& taskName)					
{											
	ImmediateTask::pointer pNewObj(new ImmediateTask());
	ImmediateTask::imp_pointer pImp(new ImmediateTaskImp(pNewObj, taskName));
	pNewObj->SetImp(pImp);

	return pNewObj;							
}
