#pragma once

// The IHostService encapsulates all the changes of the system services.

#include "BrainSystem.h" // BRAINEXPORT

class IOSProvider;
class IBehaviorBuilder;
// class ILogger;
// class IDataBaseStorage;

class BRAINEXPORT IHostService
{
public:
	virtual ~IHostService(){}

	virtual IOSProvider*		GetOSProvider() = 0;
	virtual IBehaviorBuilder*	GetBehaviorBuilder() = 0;
};
