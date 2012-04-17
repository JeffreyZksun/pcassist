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

ImmediateTask::pointer ImmediateTask::Create(const WString& taskId)					
{											
	ImmediateTask::pointer pNewObj(new ImmediateTask());
	ImmediateTask::imp_pointer pImp(new ImmediateTaskImp(pNewObj, taskId));
	pNewObj->SetImp(pImp);

	return pNewObj;							
}

void ImmediateTask::AppendAction(const WString& actionId)
{
	ImmediateTask::imp_pointer pImp =  boost::dynamic_pointer_cast<ImmediateTaskImp>(GetImp());
	if(pImp)
		pImp->AppendAction(actionId);
}

size_t ImmediateTask::GetActionCount()
{
	ImmediateTask::imp_pointer pImp =  boost::dynamic_pointer_cast<ImmediateTaskImp>(GetImp());
	if(pImp)
		return pImp->GetActionCount();

	return 0;
}
