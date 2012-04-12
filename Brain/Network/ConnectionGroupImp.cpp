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
    , m_HasPendingDisconnectionEvent(false)
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

    ProcessPendingEvents();

    for(ConnectionPointList::iterator it = m_ConnectionList.begin(); it != m_ConnectionList.end(); ++it)
    {
        (*it)->Close();
    }

    m_io_service.stop();

    m_ConnectionList.clear();
}

void ConnectionGroupImp::Add(Ts::IConnectionPointPtr spConnectionPoint)
{
    RECURSIVE_LOCK_GUARD(ComponetMutexs::GetNetworkMutex());

    ProcessPendingEvents();

    m_ConnectionList.push_back(spConnectionPoint);
}

void ConnectionGroupImp::Send(const WString& message)
{
    RECURSIVE_LOCK_GUARD(ComponetMutexs::GetNetworkMutex());

    ProcessPendingEvents();

    for(ConnectionPointList::iterator it = m_ConnectionList.begin(); it != m_ConnectionList.end(); ++it)
    {
        (*it)->Send(message);
    }
}

Ts::IConnectionPointPtr ConnectionGroupImp::GetConnectionPoint(std::size_t index) const
{
    RECURSIVE_LOCK_GUARD(ComponetMutexs::GetNetworkMutex());

    ConnectionGroupImp* pThis = const_cast<ConnectionGroupImp*>(this);
    pThis->ProcessPendingEvents();

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

    // In the connection point, there are two async handlers (read and write) in the same thread.
    // When the remote client is closed, one async handler will throw an exception. We'll disconnect
    // the connection. Even if we delete the connection point object in the first async handler, the other
    // async handler will still be called. It will result in crash due to the second handler is running on
    // a deleted object.
    // 
    // To resolve this issue, we just pending this event here. Make the related operation during the next access
    // to this object.

    m_HasPendingDisconnectionEvent = true;
}

void ConnectionGroupImp::IOThreadEntry()
{
    boost::system::error_code ec;
    m_io_service.run(ec);

}

void ConnectionGroupImp::ProcessPendingEvents()
{
    if(m_HasPendingDisconnectionEvent)
    {
        //boost::system::error_code ec;
        //m_io_service.poll(ec);  // ToDo - It would hang here.

        ConnectionPointList::iterator it = m_ConnectionList.begin();
        while (  it != m_ConnectionList.end())
        {
            if((*it)->IsConnected())
            {
                ++it;
            }
            else
            {
                it = m_ConnectionList.erase(it);
            }
        }

        m_HasPendingDisconnectionEvent = false;
    }
}

