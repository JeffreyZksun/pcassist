#pragma once


#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

#include <Diagnostics.h>

#include <string>
typedef std::wstring    WString; // Wide string
typedef std::string     NString; // Narrow string

class ITaskSystem;
typedef boost::shared_ptr<ITaskSystem>	ITaskSystemPtr;

namespace Ts
{
	class ITaskManager;
	class ITask;

	typedef boost::shared_ptr<ITaskManager>		ITaskManagerPtr;
	typedef boost::shared_ptr<ITask>			ITaskPtr;
}
