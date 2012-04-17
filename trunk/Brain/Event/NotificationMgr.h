#pragma once

#include "INotificationMgr.h"
#include "ThreadSafeSingleton.h"

namespace Ts
{

    class NotificationMgrImp;

    class BRAINEXPORT NotificationMgr : public INotificationMgr
    {
    public:
        virtual ~NotificationMgr(void);

    public:
        THREADSAFE_SINGLETON_DECL(NotificationMgr)

    public:
        virtual void            Subscribe(IEventSource*, IEventSink*, IEventFilter*);
        virtual void            Unsubscribe(IEventSource*, IEventSink*);
        virtual void            Fire(IEvent*);

    private:
        // Disable it
        NotificationMgr();

    private:
        NotificationMgrImp*     m_Imp;
    };

}
