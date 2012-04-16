#pragma once

#include "BrainSystem.h"

class TaskManager;
class BehaviorBodyFactory;
class VariableManager;
class IOSProvider;
class IHostService;
class Database;

class BRAINEXPORT ITaskSystem
{
public:
	virtual ~ITaskSystem(){};

public:
	virtual TaskManager*			GetTaskManager() const = 0;
	virtual BehaviorBodyFactory*	GetBehaviorBodyFactory() const = 0;
	virtual VariableManager*		GetVariableManager() const = 0;
	virtual IOSProvider*			GetOSProvider() const = 0;
	virtual Database*				GetDatabase() const = 0;
};
