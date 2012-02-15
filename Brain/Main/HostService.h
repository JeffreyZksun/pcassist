#pragma once

#include "IHostService.h"

class HostService : public IHostService
{
public:
	HostService();
	virtual ~HostService();

	virtual IOSProvider*		GetOSProvider();
	virtual IBehaviorBuilder*	GetBehaviorBuilder();

private:
	IOSProvider*				mpProvider;
	IBehaviorBuilder*			mpBehaviorBuilder;
};
