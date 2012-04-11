#include "stdafx.h"

#include "NetworkEvents.h"

using namespace Ts;

/****************************************************/
//              NetworkMessageEvent
/****************************************************/
NetworkMessageEvent::NetworkMessageEvent(Ts::IConnectionPoint* pConnectionPoint, const WString& message) : m_pConnectionPoint(pConnectionPoint), m_Message(message)
{

}

NetworkMessageEvent::~NetworkMessageEvent(void)
{
    // the m_pConnectionPoint is deleted by its owner.
}

Ts::IConnectionPoint* NetworkMessageEvent::GetConnectionPoint() const
{
    return m_pConnectionPoint;
}

const WString& NetworkMessageEvent::GetMessage() const
{
    return m_Message;
}

IEventSource* NetworkMessageEvent::GetEventSource() const
{
    return NetworkEventSource::Get();
}

IEventDispatcher* NetworkMessageEvent::GetEventDispatcher() const
{
    return NetworkMessageEventDispatcher::Get();
}

unsigned int NetworkMessageEvent::GetType() const
{
    return 0;
}

IEvent::ETime NetworkMessageEvent::GetTime() const
{
    return ePost;
}

/****************************************************/
//              NetworkMessageEventDispatcher
/****************************************************/
THREADSAFE_SINGLETON_IMPL(NetworkMessageEventDispatcher)
    
bool NetworkMessageEventDispatcher::Fire(IEvent* pEvent, IEventSink* pSink) const 
{
    if(NULL == pEvent || NULL == pSink)
        return false;

    NetworkMessageEvent* pNwEvent = dynamic_cast<NetworkMessageEvent*>(pEvent);
    if(NULL == pNwEvent)
        return false;

    NetworkMessageEventSink* pNwSink = dynamic_cast<NetworkMessageEventSink*>(pSink);
    if(NULL == pNwSink)
        return false;

    pNwSink->OnMessageReceived(pNwEvent);

    return true;
}

/****************************************************/
//              NetworkEventSource
/****************************************************/
THREADSAFE_SINGLETON_IMPL(NetworkEventSource)

/****************************************************/
//              NetworkMessageEventFilter
/****************************************************/
bool NetworkMessageEventFilter::Applicable(IEvent* pEvent) const
{
    if(NULL == pEvent)
        return false;

    NetworkMessageEvent* pNwEvent = dynamic_cast<NetworkMessageEvent*>(pEvent);
    if(NULL == pNwEvent)
        return false;

    return true;
}


/****************************************************/
//              NetworkConnectionEvent
/****************************************************/
NetworkConnectionEvent::NetworkConnectionEvent(Ts::IConnectionPoint* pConnectionPoint, EConnectionEventType eType) : m_pConnectionPoint(pConnectionPoint), m_eType(eType)
{

}

NetworkConnectionEvent::~NetworkConnectionEvent(void)
{
    // the m_pConnectionPoint is deleted by its owner.
}

Ts::IConnectionPoint* NetworkConnectionEvent::GetConnectionPoint() const
{
    return m_pConnectionPoint;
}

IEventSource* NetworkConnectionEvent::GetEventSource() const
{
    return NetworkEventSource::Get();
}

IEventDispatcher* NetworkConnectionEvent::GetEventDispatcher() const
{
    return NetworkConnectionEventDispatcher::Get();
}

unsigned int NetworkConnectionEvent::GetType() const
{
    return (unsigned int)m_eType;
}

IEvent::ETime NetworkConnectionEvent::GetTime() const
{
    return ePost;
}

/****************************************************/
//              NetworkConnectionEventDispatcher
/****************************************************/
THREADSAFE_SINGLETON_IMPL(NetworkConnectionEventDispatcher)

bool NetworkConnectionEventDispatcher::Fire(IEvent* pEvent, IEventSink* pSink) const 
{
    if(NULL == pEvent || NULL == pSink)
        return false;

    NetworkConnectionEvent* pNwEvent = dynamic_cast<NetworkConnectionEvent*>(pEvent);
    if(NULL == pNwEvent)
        return false;

    NetworkConnectionEventSink* pNwSink = dynamic_cast<NetworkConnectionEventSink*>(pSink);
    if(NULL == pNwSink)
        return false;

    switch(pNwEvent->GetType())
    {
    case NetworkConnectionEvent::eConnect:
        pNwSink->OnConnected(pNwEvent);
        break;
    case NetworkConnectionEvent::eDisconnect:
        pNwSink->OnDisconnected(pNwEvent);
        break;
    default:
        break;
        // ToDo - assert it.
    }



    return true;
}
