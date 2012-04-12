#pragma once

#include <boost/thread.hpp>

#define RECURSIVE_LOCK_GUARD(theMutex) boost::lock_guard<boost::recursive_mutex> guard(theMutex);

namespace Ts
{
    class ComponetMutexs
    {
    public:
        static boost::recursive_mutex& GetNetworkMutex();
    };

}
