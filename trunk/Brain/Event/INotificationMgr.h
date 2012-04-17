#pragma once

// The event manager saves all the subscribed the event sink. It know which event should be fired to which sink.
// The event saves all the event data.
// The event dispatcher knows how to fire the event to the sink. It doesn't saves any data. 
//      It casts the event and sink to the concrete type and calls the concrete event functions.
// The event sink is the event receiver and implements the functions called by the event dispatcher. 
//      It is interested in the event of the source specified by the event filter.
// The event filter is used to check if a event is interested by the sink.

namespace Ts
{

    class IEventSource;
    class IEvent;
    class IEventSink;
    class IEventFilter;

    class BRAINEXPORT INotificationMgr
    {
    public:
        virtual ~INotificationMgr(void){};

        virtual void            Subscribe(IEventSource*, IEventSink*, IEventFilter*) = 0;
        virtual void            Unsubscribe(IEventSource*, IEventSink*) = 0;
        virtual void            Fire(IEvent*) = 0;
    };

}