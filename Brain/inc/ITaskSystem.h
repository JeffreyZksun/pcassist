#pragma once

#include "BrainSystem.h"

class BehaviorManager;
class BehaviorBodyFactory;
class VariableManager;
class IOSProvider;
class IHostService;
class Database;

namespace Ts
{
	class ITaskManager;

	typedef boost::shared_ptr<ITaskManager> ITaskManagerPtr;
}

class BRAINEXPORT ITaskSystem
{
public:
	virtual ~ITaskSystem(){};

public:
	virtual BehaviorManager*		GetBehaviorManager() const = 0;
	virtual BehaviorBodyFactory*	GetBehaviorBodyFactory() const = 0;
	virtual VariableManager*		GetVariableManager() const = 0;
	virtual IOSProvider*			GetOSProvider() const = 0;
	virtual Database*				GetDatabase() const = 0;
	virtual Ts::ITaskManagerPtr		GetTaskManager() const = 0;
};
