#pragma once

#include "stdafx.h"

#include "ConditionalTask.h"
#include "ConditionalTaskImp.h"

using namespace Ts;


ConditionalTask::ConditionalTask() : TaskBase()					
{											
}											

ConditionalTask::~ConditionalTask()
{

}

ConditionalTask::pointer ConditionalTask::Create(const WString& taskName, const WString& conditionName, const WString& decoratedTaskName)					
{											
	ConditionalTask::pointer pNewObj(new ConditionalTask());	
	ConditionalTask::imp_pointer pImp(new ConditionalTaskImp(pNewObj, taskName, conditionName, decoratedTaskName));
	pNewObj->SetImp(pImp);

	return pNewObj;							
}
