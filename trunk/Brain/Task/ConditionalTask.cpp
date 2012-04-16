#pragma once

#include "stdafx.h"

#include "ConditionalTask.h"
#include "ConditionalTaskImp.h"

using namespace Ts;


ConditionalTask::ConditionalTask() : m_pImp()						
{											
}											

ConditionalTask::~ConditionalTask()
{

}

ConditionalTask::pointer ConditionalTask::Create()					
{											
	ConditionalTask::pointer pNewObj(new ConditionalTask());		
	pNewObj->m_pImp.reset(new ConditionalTaskImp(pNewObj));

	return pNewObj;							
}

bool ConditionalTask::IsReady()
{
	return m_pImp->IsReady();
}

bool ConditionalTask::Execute()
{
	return m_pImp->Execute();
}