#include "stdafx.h"


#include "ConnectionGroupImp.h"
#include "ConnectionPoint.h"
#include "ThreadLocks.h"
#include "NotificationMgr.h"


using namespace Ts;

ConnectionGroupImp::ConnectionGroupImp() 
    :m_mutexConnectionList(), m_ConnectionList(), m_io_service(), m_pAsioThread(NULL)
{
     NotificationMgr::Get()->Subscribe(NetworkEventSource::Get(), this, &m_EventFilter);
}

ConnectionGroupImp::~ConnectionGroupImp(void)
{
    NotificationMgr::Get()->Unsubscribe(NetworkEventSource::Get(), this);
    Close();
}

void ConnectionGroupImp::Start()
{
    // Run the asio tasks in the working thread.
    if(NULL == m_pAsioThread)
        m_pAsioThread = new boost::thread(boost::bind( &ConnectionGroupImp::IOThreadEntry, this));
}

void ConnectionGroupImp::Close()
{
    RECURSIVE_LOCK_GUARD(m_mutexConnectionList);
    for(ConnectionPointList::iterator it = m_ConnectionList.begin(); it != m_ConnectionList.end(); ++it)
    {
        (*it)->Close();
    }

    m_io_service.stop();

    // Stop the asio
    if(m_pAsioThread != NULL)
    {
        // ToDo - Do we need to kill the thread?
        delete m_pAsioThread;
        m_pAsioThread = NULL;
    }

    while (!m_ConnectionList.empty())
    {
        IConnectionPoint* pCP = m_ConnectionList.back();
        delete pCP;
        m_ConnectionList.pop_back();
    }
}

void ConnectionGroupImp::Add(Ts::IConnectionPoint* pConnectionPoint)
{
    RECURSIVE_LOCK_GUARD(m_mutexConnectionList);
    m_ConnectionList.push_back(pConnectionPoint);
}

void ConnectionGroupImp::Send(const WString& message)
{
    RECURSIVE_LOCK_GUARD(m_mutexConnectionList);
    for(ConnectionPointList::iterator it = m_ConnectionList.begin(); it != m_ConnectionList.end(); ++it)
    {
        (*it)->Send(message);
    }
}

Ts::IConnectionPoint* ConnectionGroupImp::GetConnectionPoint(std::size_t index) const
{
    RECURSIVE_LOCK_GUARD(m_mutexConnectionList);

    if(m_ConnectionList.size() <= index)
        return NULL;

    std::size_t i = 0;
    for(ConnectionPointList::const_iterator it = m_ConnectionList.begin(); it != m_ConnectionList.end(); ++it)
    {
        if(i == index)
            return *it;

        i++;
    }

    return NULL;
}

boost::asio::io_service& ConnectionGroupImp::io_service()
{
    return m_io_service;
}

void ConnectionGroupImp::OnConnected(NetworkConnectionEvent* pEvent)
{
    // Do nothing.
}

void ConnectionGroupImp::OnDisconnected(NetworkConnectionEvent* pEvent)
{
    if(pEvent->GetConnectionPoint() == NULL)
        return;

    RECURSIVE_LOCK_GUARD(m_mutexConnectionList);

    // It will crash when delete the connection pointer. We need to find a good solution to handle the pointers.

    //ConnectionPointList::iterator it = std::find(m_ConnectionList.begin(), m_ConnectionList.end(), pEvent->GetConnectionPoint());
    //if(it != m_ConnectionList.end())
    //{
    //    m_ConnectionList.erase(it);
    //    delete pEvent->GetConnectionPoint();
    //}
}

void ConnectionGroupImp::IOThreadEntry()
{
    try
    {
        m_io_service.run();
    }
    catch (... )
    {
        // The run always throws the exception.
    }
}

