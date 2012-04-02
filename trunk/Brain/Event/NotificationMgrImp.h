#pragma once

#include <map>

namespace Ts
{

    class NotificationMgr;
    class IEventSource;
    class IEvent;
    class IEventSink;
    class IEventFilter;

    class EventFilterCollection;


    class NotificationMgrImp
    {
    public:
        NotificationMgrImp(NotificationMgr* pSelf);
        ~NotificationMgrImp(void);

        NotificationMgr*    Self() const;

    public:
        void                Subscribe(IEventSource*, IEventSink*, IEventFilter*);
        void                Unsubscribe(IEventSource*, IEventSink*);
        void                Fire(IEvent*);

    public:
        typedef std::map<IEventSink*, EventFilterCollection*> SinkMap;
        typedef std::map<IEventSource*, SinkMap> SourceMap;

    private:
        NotificationMgr*          m_pSelf;

        SourceMap                 m_Eventmap;
    };

}