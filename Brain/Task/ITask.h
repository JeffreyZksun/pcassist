#pragma once

#include <boost/enable_shared_from_this.hpp>

class ITaskSystem;

namespace Ts
{

    class ITask : public boost::enable_shared_from_this<ITask>		
    {
    public:
        virtual ~ITask(void){};

		virtual bool            IsReady(ITaskSystem* pTaskSystem) const = 0;
		virtual bool            Execute(ITaskSystem* pTaskSystem) = 0;
		virtual	const WString&	GetName() const = 0;
    };
}