#pragma once

namespace Ts
{

    class IEvent;

    class BRAINEXPORT IEventFilter
    {
    public:
        virtual ~IEventFilter(void){};

    public: 
        virtual bool Applicable(IEvent* ) const = 0;
    };
}