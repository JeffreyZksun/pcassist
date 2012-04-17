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

ConditionalTask::pointer ConditionalTask::Create(const WString& taskId, const WString& conditionName, ITaskPtr pDecoratedTask)					
{											
	ConditionalTask::pointer pNewObj(new ConditionalTask());	
	ConditionalTask::imp_pointer pImp(new ConditionalTaskImp(pNewObj, taskId, conditionName, pDecoratedTask));
	pNewObj->SetImp(pImp);

	return pNewObj;							
}
