#include "stdafx.h"

#include "ThreadLocks.h"

using namespace Ts;

boost::recursive_mutex s_networkMutex;

boost::recursive_mutex& ComponetMutexs::GetNetworkMutex()
{
    return s_networkMutex;
}


