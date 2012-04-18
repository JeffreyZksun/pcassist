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

ConditionalTask::pointer ConditionalTask::Create(const WString& taskId, const WString& conditionId, const WString& decoratedTaskId)					
{											
	ConditionalTask::pointer pNewObj(new ConditionalTask());	
	ConditionalTask::imp_pointer pImp(new ConditionalTaskImp(pNewObj, taskId, conditionId, decoratedTaskId));
	pNewObj->SetImp(pImp);

	return pNewObj;							
}


