#pragma once

namespace Ts
{

    class IEventSource;
    class IEventDispatcher;

    class BRAINEXPORT IEvent
    {
    public:
        virtual ~IEvent(void){};

        enum ETime
        {
            ePre = 0,
            ePost
        };

        virtual IEventSource*       GetEventSource() const= 0;
        virtual IEventDispatcher*   GetEventDispatcher() const= 0;
        virtual unsigned int        GetType() const = 0;
        virtual ETime               GetTime() const = 0;
    };

}
