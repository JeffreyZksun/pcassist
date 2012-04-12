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
    typedef boost::shared_ptr<IConnectionPoint>     IConnectionPointPtr;

    /****************************************************/
    //              NetworkMessageEvent
    /****************************************************/
    class NetworkMessageEvent : public IEvent
    {
    public:
        NetworkMessageEvent(Ts::IConnectionPointPtr pConnectionPoint, const WString& message);
        virtual ~NetworkMessageEvent(void);

    public:
        virtual IEventSource*       GetEventSource() const;
        virtual IEventDispatcher*   GetEventDispatcher() const;
        virtual unsigned int        GetType() const;
        virtual ETime               GetTime() const;


    public:
        virtual IConnectionPointPtr       GetConnectionPoint() const;
        virtual const WString&                  GetMessage() const;


    private:
        IConnectionPointPtr	        m_pConnectionPoint;
        WString					    m_Message;

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
    //              NetworkEventSource
    /****************************************************/

    class NetworkEventSource: public IEventSource
    {
    public:
        virtual ~NetworkEventSource(void){};

    public:
        THREADSAFE_SINGLETON_DECL(NetworkEventSource)

    private:
        // Disable it
        NetworkEventSource(){};
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

    /****************************************************/
    //              NetworkConnectionEvent
    /****************************************************/
    class NetworkConnectionEvent : public IEvent
    {
    public:
        enum EConnectionEventType
        {
            eConnect,
            eDisconnect
        };

    public:
        NetworkConnectionEvent(Ts::IConnectionPointPtr pConnectionPoint, EConnectionEventType eType);
        virtual ~NetworkConnectionEvent(void);

    public:
        virtual IEventSource*       GetEventSource() const;
        virtual IEventDispatcher*   GetEventDispatcher() const;
        virtual unsigned int        GetType() const;
        virtual ETime               GetTime() const;


    public:
        virtual Ts::IConnectionPointPtr       GetConnectionPoint() const;

    private:
        Ts::IConnectionPointPtr	        m_pConnectionPoint;
        EConnectionEventType            m_eType;
    };

    /****************************************************/
    //              NetworkMessageEventDispatcher
    /****************************************************/

    class NetworkConnectionEventDispatcher: public IEventDispatcher
    {
    public:
        virtual ~NetworkConnectionEventDispatcher(void){};

        THREADSAFE_SINGLETON_DECL(NetworkConnectionEventDispatcher)


    public:
        virtual bool Fire(IEvent*, IEventSink*) const ;

    private:
        // Disable it
        NetworkConnectionEventDispatcher(){};
    };

    /****************************************************/
    //              NetworkMessageEventSink
    /****************************************************/

    class NetworkConnectionEventSink: public IEventSink
    {
    public:
        virtual ~NetworkConnectionEventSink(void){};

    public:
        virtual void OnConnected(NetworkConnectionEvent* pEvent) = 0;
        virtual void OnDisconnected(NetworkConnectionEvent* pEvent) = 0;

    };

}