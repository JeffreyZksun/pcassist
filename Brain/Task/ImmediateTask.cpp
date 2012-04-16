#pragma once

#include "stdafx.h"

#include "ImmediateTask.h"
#include "ImmediateTaskImp.h"

using namespace Ts;


ImmediateTask::ImmediateTask() : m_pImp()						
{											
}											

ImmediateTask::~ImmediateTask()
{

}

ImmediateTask::pointer ImmediateTask::Create()					
{											
	ImmediateTask::pointer pNewObj(new ImmediateTask());		
	pNewObj->m_pImp.reset(new ImmediateTaskImp(pNewObj));

	return pNewObj;							
}

bool ImmediateTask::IsReady()
{
	return m_pImp->IsReady();
}

bool ImmediateTask::Execute()
{
	return m_pImp->Execute();
}