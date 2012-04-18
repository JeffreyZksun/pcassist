#pragma once

#include "stdafx.h"

#include "TaskBase.h"
#include "TaskBaseImp.h"

using namespace Ts;


TaskBase::TaskBase() : m_pImp()						
{											
}											

TaskBase::~TaskBase()
{

}

bool TaskBase::IsReady(ITaskSystem* pTaskSystem) const
{
	return m_pImp->IsReady(pTaskSystem);
}

WString TaskBase::GetObjectId() const
{
	return m_pImp->GetObjectId();
}

bool TaskBase::Execute(ITaskSystem* pTaskSystem)
{
	return m_pImp->Execute(pTaskSystem);
}

TaskBase::imp_pointer TaskBase::GetImp() const
{
	return m_pImp;
}

void TaskBase::SetImp(imp_pointer pImp)
{
	m_pImp = pImp;
}

