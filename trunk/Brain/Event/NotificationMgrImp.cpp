#pragma once

#include "stdafx.h"

#include "NotificationMgrImp.h"
#include "IEvent.h"
#include "IEventSink.h"
#include "IEventDispatcher.h"
#include "IEventSource.h"
#include "IEventFilter.h"

#include <list>
#include <algorithm>
#include <set>

using namespace Ts;

/**********************************************************************/
namespace Ts
{


class EventFilterCollection
{
public:
    EventFilterCollection();
    ~EventFilterCollection();

    void Add(IEventFilter*);
    void Remove(IEventFilter*);

    bool Applicable(IEvent*) const;


    typedef std::list<IEventFilter*> FilterList;

private:
    FilterList  m_Filters;
};
}

EventFilterCollection::EventFilterCollection() : m_Filters()
{

}

EventFilterCollection::~EventFilterCollection() 
{
    // Do nothing to m_Filters.
}

void EventFilterCollection::Add(IEventFilter* pFilter)
{
    if(NULL == pFilter)
        return;

    FilterList::iterator it = std::find(m_Filters.begin(), m_Filters.end(), pFilter);
    if(it != m_Filters.end())
        return;

    m_Filters.push_back(pFilter);
}

void EventFilterCollection::Remove(IEventFilter* pFilter)
{
    if(NULL == pFilter)
        return;

    FilterList::iterator it = std::find(m_Filters.begin(), m_Filters.end(), pFilter);
    if(it != m_Filters.end())
    {
        m_Filters.erase(it);
    }
}

bool EventFilterCollection::Applicable(IEvent* pEvent) const
{
    if(NULL == pEvent)
        return false;

    for(FilterList::const_iterator it = m_Filters.begin(); it != m_Filters.end(); ++it)
    {
        if((*it)->Applicable(pEvent))
            return true;
    }

    return false;
}

/***************************ScopedCyclicDetector*********************************************/
class ScopedCyclicDetector
{
public:
    ScopedCyclicDetector(IEventSource* pSource)
    {
        m_bHasCycling = false;
        m_pSource = NULL;

        if(GetEventSourceSet().find(pSource) != GetEventSourceSet().end())
        {
            // Dead lock detected.
            m_bHasCycling = true;
            return;
        }

        m_pSource = pSource;

        GetEventSourceSet().insert(pSource);
    }

    ~ScopedCyclicDetector()
    {
        if(NULL != m_pSource)
        {
            EventSourceSet::iterator it = GetEventSourceSet().find(m_pSource);
            if(it != GetEventSourceSet().end())
                GetEventSourceSet().erase(it);
        }
    }

    bool HasCycling() const
    {
        return m_bHasCycling;
    }

    typedef std::set<IEventSource*> EventSourceSet;

    static  EventSourceSet& GetEventSourceSet()
    {
        static ScopedCyclicDetector::EventSourceSet s_TheOneAndOnlyOne;
        return s_TheOneAndOnlyOne;
    }

private:

    bool            m_bHasCycling;
    IEventSource*   m_pSource;
};

/************************************************************************/

NotificationMgrImp::NotificationMgrImp(NotificationMgr* pSelf) 
    : m_pSelf(pSelf), m_Eventmap()
{
}

NotificationMgrImp::~NotificationMgrImp(void)
{
    // Delete the filter collections.

    for(SourceMap::iterator itSource = m_Eventmap.begin(); itSource != m_Eventmap.end(); ++itSource)
    {
        SinkMap& sinkMap = itSource->second;

        for(SinkMap::iterator itSink = sinkMap.begin(); itSink != sinkMap.end(); ++itSink)
        {
            EventFilterCollection* pFilterCollcetion = itSink->second;
            delete pFilterCollcetion;
        }

        sinkMap.clear();
    } 

    m_Eventmap.clear();
}

NotificationMgr* NotificationMgrImp::Self() const
{
    return m_pSelf;
}

void NotificationMgrImp::Subscribe(IEventSource* pSource, IEventSink* pSink, IEventFilter* pFilter)
{
    SourceMap::iterator itSource = m_Eventmap.find(pSource);
    if(itSource != m_Eventmap.end())
    {
        SinkMap& sinkMap = itSource->second;

        SinkMap::iterator itSink = sinkMap.find(pSink);
        if(itSink != sinkMap.end())
        {
            EventFilterCollection* pFilterConnection = itSink->second;
            pFilterConnection->Add(pFilter);
        }
        else
        {
            // Add new item
            EventFilterCollection* pFilterConnection = new EventFilterCollection();
            pFilterConnection->Add(pFilter);

            sinkMap.insert(SinkMap::value_type(pSink, pFilterConnection));
        }
    }
    else
    {
        EventFilterCollection* pFilterConnection = new EventFilterCollection();
        pFilterConnection->Add(pFilter);

        SinkMap sinkMap;
        sinkMap.insert(SinkMap::value_type(pSink, pFilterConnection));

        m_Eventmap.insert(SourceMap::value_type(pSource, sinkMap));
    }
}

void NotificationMgrImp::Unsubscribe(IEventSource* pSource, IEventSink* pSink)
{
    SourceMap::iterator itSource = m_Eventmap.find(pSource);
    if(itSource != m_Eventmap.end())
    {
        SinkMap& sinkMap = itSource->second;

        SinkMap::iterator itSink = sinkMap.find(pSink);
        if(itSink != sinkMap.end())
        {
            EventFilterCollection* pFilterCollcetion = itSink->second;
            delete pFilterCollcetion;

            sinkMap.erase(itSink);

            if (sinkMap.empty())
            {
                m_Eventmap.erase(itSource);
            }
        }
    } 
}


void NotificationMgrImp::Fire(IEvent* pEvent)
{
    if(NULL == pEvent)
        return;
 
    IEventSource* pSource = pEvent->GetEventSource();
    if(NULL == pSource)
        return;

     // We support event nest, but should avoid the dead lock. 
    ScopedCyclicDetector dt(pSource);
    if(dt.HasCycling())
    {
        DATA_ASSERT(!_T("ERROR: Cyclic envent loop is detected. Ignore the current event."))
        return;
    }

    SourceMap::iterator itSource = m_Eventmap.find(pSource);
    if(itSource != m_Eventmap.end())
    {
        SinkMap& sinkMap = itSource->second;

        for(SinkMap::iterator itSink = sinkMap.begin(); itSink != sinkMap.end(); ++itSink)
        {
            EventFilterCollection* pFilterCollcetion = itSink->second;
            if(pFilterCollcetion != NULL && pFilterCollcetion->Applicable(pEvent))
            {
                IEventSink* pSink = itSink->first;
                IEventDispatcher* pDispatcher = pEvent->GetEventDispatcher();
                if(pDispatcher != NULL)
                {
                    bool ret = pDispatcher->Fire(pEvent, pSink);
                }
            }
        }
    } 
}