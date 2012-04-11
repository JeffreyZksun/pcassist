#pragma once

#include "IEventFilter.h"

namespace Ts
{
    class DefaultFilter: public IEventFilter
    {
    public:
        virtual ~DefaultFilter(void){};

    public:
        virtual bool Applicable(IEvent*) const;
    };

}
