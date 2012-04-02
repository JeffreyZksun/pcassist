#pragma once

#include "stdafx.h"

#include "NotificationMgr.h"
#include "NotificationMgrImp.h"

using namespace Ts;

THREADSAFE_SINGLETON_IMPL(NotificationMgr)

NotificationMgr::NotificationMgr() : m_Imp(NULL)
{
    m_Imp = new NotificationMgrImp(this);
}

NotificationMgr::~NotificationMgr()
{

}

void NotificationMgr::Subscribe(IEventSource* pSource, IEventSink* pSink, IEventFilter* pFilter)
{
    m_Imp->Subscribe(pSource, pSink, pFilter);
}

void NotificationMgr::Unsubscribe(IEventSource* pSource, IEventSink* pSink)
{
    m_Imp->Unsubscribe(pSource, pSink);
}

void NotificationMgr::Fire(IEvent* pEvent)
{
    m_Imp->Fire(pEvent);
}