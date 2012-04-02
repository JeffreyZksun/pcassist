#pragma once

#include "IEvent.h"
#include "IEventSink.h"
#include "IEventDispatcher.h"
#include "IEventSource.h"
#include "IEventFilter.h"

#include "ThreadSafeSingleton.h"

namespace Ts
{

    class IConnectionPoint;

    /****************************************************/
    //              NetworkMessageEvent
    /****************************************************/
    class NetworkMessageEvent : public IEvent
    {
    public:
        NetworkMessageEvent(Ts::IConnectionPoint* pConnectionPoint, const WString& message);
        virtual ~NetworkMessageEvent(void);

    public:
        virtual IEventSource*       GetEventSource() const;
        virtual IEventDispatcher*   GetEventDispatcher() const;
        virtual unsigned int        GetType() const;
        virtual ETime               GetTime() const;


    public:
        virtual IConnectionPoint*       GetConnectionPoint() const;
        virtual const WString&          GetMessage() const;


    private:
        Ts::IConnectionPoint*	m_pConnectionPoint;
        WString					m_Message;

    };

    /****************************************************/
    //              NetworkMessageEventSink
    /****************************************************/

    class NetworkMessageEventSink: public IEventSink
    {
    public:
        virtual ~NetworkMessageEventSink(void){};

    public:
        virtual void OnMessageReceived(NetworkMessageEvent* pEvent) = 0;

    };

    /****************************************************/
    //              NetworkMessageEventDispatcher
    /****************************************************/

    class NetworkMessageEventDispatcher: public IEventDispatcher
    {
    public:
        virtual ~NetworkMessageEventDispatcher(void){};

        THREADSAFE_SINGLETON_DECL(NetworkMessageEventDispatcher)


    public:
        virtual bool Fire(IEvent*, IEventSink*) const ;

    private:
        // Disable it
        NetworkMessageEventDispatcher(){};
    };

    /****************************************************/
    //              NetworkMessageEventSource
    /****************************************************/

    class NetworkMessageEventSource: public IEventSource
    {
    public:
        virtual ~NetworkMessageEventSource(void){};

    public:
        THREADSAFE_SINGLETON_DECL(NetworkMessageEventSource)

    private:
        // Disable it
        NetworkMessageEventSource(){};
    };

    /****************************************************/
    //              NetworkMessageEventFilter
    /****************************************************/

    class NetworkMessageEventFilter: public IEventFilter
    {
    public:
        virtual ~NetworkMessageEventFilter(void){};

    public:
        virtual bool Applicable(IEvent*) const;
    };

}