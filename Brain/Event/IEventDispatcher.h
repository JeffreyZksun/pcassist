#pragma once

namespace Ts
{

    class IEvent;
    class IEventSink;

    class BRAINEXPORT IEventDispatcher
    {
    public:
        virtual ~IEventDispatcher(void){};

    public:
        virtual bool Fire(IEvent*, IEventSink*) const = 0;
    };

}
