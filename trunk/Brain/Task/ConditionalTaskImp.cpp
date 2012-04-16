#pragma once

#include "stdafx.h"

#include "ConditionalTaskImp.h"

using namespace Ts;

ConditionalTaskImp::ConditionalTaskImp(owner_weak_pointer pSelf)			
	: m_pSelf(pSelf)						
{											
}											

ConditionalTaskImp::owner_pointer ConditionalTaskImp::Self() const		
{											
	return m_pSelf.lock();					
}

bool ConditionalTaskImp::IsReady()
{
	return true;
}

bool ConditionalTaskImp::Execute()
{
	// Todo
	return false;
}