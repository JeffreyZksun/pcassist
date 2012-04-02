#include "stdafx.h"

#include "NetworkMessageEvent.h"

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
    return NetworkMessageEventSource::Get();
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
//              NetworkMessageEventSource
/****************************************************/
THREADSAFE_SINGLETON_IMPL(NetworkMessageEventSource)

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