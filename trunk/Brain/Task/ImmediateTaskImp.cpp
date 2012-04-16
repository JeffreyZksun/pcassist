#pragma once

#include "stdafx.h"

#include "ImmediateTaskImp.h"

using namespace Ts;

ImmediateTaskImp::ImmediateTaskImp(owner_weak_pointer pSelf)			
	: m_pSelf(pSelf)						
{											
}											

ImmediateTaskImp::owner_pointer ImmediateTaskImp::Self() const		
{											
	return m_pSelf.lock();					
}

bool ImmediateTaskImp::IsReady()
{
	return true;
}

bool ImmediateTaskImp::Execute()
{
	// Todo
	return false;
}