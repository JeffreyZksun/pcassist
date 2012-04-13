#include "stdafx.h"

#include "ConnectionGroupImp.h"
#include "ConnectionPoint.h"
#include "ThreadLocks.h"
#include "NotificationMgr.h"
#include "ThreadLocks.h"


using namespace Ts;

ConnectionGroupImp::ConnectionGroupImp() 
    : m_ConnectionList()
    , m_io_service()
    , m_pAsioThread()
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
        m_pAsioThread.reset(new boost::thread(boost::bind( &ConnectionGroupImp::IOThreadEntry, this)));
}

void ConnectionGroupImp::Close()
{
    RECURSIVE_LOCK_GUARD(ComponetMutexs::GetNetworkMutex());

    m_io_service.stop();

    m_ConnectionList.clear();
}

void ConnectionGroupImp::Add(Ts::IConnectionPointPtr spConnectionPoint)
{
    RECURSIVE_LOCK_GUARD(ComponetMutexs::GetNetworkMutex());


    m_ConnectionList.push_back(spConnectionPoint);
}

void ConnectionGroupImp::Send(const WString& message)
{
    RECURSIVE_LOCK_GUARD(ComponetMutexs::GetNetworkMutex());


    for(ConnectionPointList::iterator it = m_ConnectionList.begin(); it != m_ConnectionList.end(); ++it)
    {
        (*it)->Send(message);
    }
}

Ts::IConnectionPointPtr ConnectionGroupImp::GetConnectionPoint(std::size_t index) const
{
    RECURSIVE_LOCK_GUARD(ComponetMutexs::GetNetworkMutex());


    if(m_ConnectionList.size() <= index)
        return IConnectionPointPtr();

    std::size_t i = 0;
    for(ConnectionPointList::const_iterator it = m_ConnectionList.begin(); it != m_ConnectionList.end(); ++it)
    {
        if(i == index)
            return *it;

        i++;
    }

    return IConnectionPointPtr();
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

    RECURSIVE_LOCK_GUARD(ComponetMutexs::GetNetworkMutex());

    ConnectionPointList::iterator it = find(m_ConnectionList.begin(), m_ConnectionList.end(), pEvent->GetConnectionPoint());
    if (it != m_ConnectionList.end())
    {
        m_ConnectionList.erase(it);
    }
}

void ConnectionGroupImp::IOThreadEntry()
{
    boost::system::error_code ec;
    m_io_service.run(ec);
}


