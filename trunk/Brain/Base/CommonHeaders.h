#pragma once


#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

#include <Diagnostics.h>

#include <string>
typedef std::wstring    WString; // Wide string
typedef std::string     NString; // Narrow string

#include "ConstantsDefinition.h"
#include "Parameter.h"
#include "ParameterTable.h"
#include "Logger.h"
#include "NotificationMgr.h"

class ITaskSystem;
class Condition;
class Action;

typedef boost::shared_ptr<ITaskSystem>	ITaskSystemPtr;
typedef boost::shared_ptr<Condition>	ConditionPtr;
typedef boost::shared_ptr<Action>		ActionPtr;

namespace Ts
{
	class ITaskManager;
	class ITask;

	typedef boost::shared_ptr<ITaskManager>		ITaskManagerPtr;
	typedef boost::shared_ptr<ITask>			ITaskPtr;
}
