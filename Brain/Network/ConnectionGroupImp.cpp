#include "stdafx.h"


#include "ConnectionGroupImp.h"
#include "ConnectionPoint.h"

using namespace Ts;

ConnectionGroupImp::ConnectionGroupImp() 
    :m_ConnectionList(), m_io_service(), m_pAsioThread(NULL)
{
}

ConnectionGroupImp::~ConnectionGroupImp(void)
{
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
    m_ConnectionList.push_back(pConnectionPoint);
}

void ConnectionGroupImp::Send(const WString& message)
{
    for(ConnectionPointList::iterator it = m_ConnectionList.begin(); it != m_ConnectionList.end(); ++it)
    {
        (*it)->Send(message);
    }
}

Ts::IConnectionPoint* ConnectionGroupImp::GetConnectionPoint(std::size_t index) const
{
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





