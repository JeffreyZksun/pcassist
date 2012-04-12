#pragma once

#include <boost/asio.hpp>
#include <boost/thread.hpp>

#include "NetworkEvents.h"
#include "EventFilters.h"


namespace Ts
{
    class IConnectionPoint;
    typedef boost::shared_ptr<IConnectionPoint>     IConnectionPointPtr;

    class ConnectionGroupImp : public NetworkConnectionEventSink
    {
    public:
        ConnectionGroupImp();
        ~ConnectionGroupImp(void);

        void                        Start();
        void                        Close();

        void                        Add(Ts::IConnectionPointPtr spConnectionPoint);
        void                        Send(const WString& message);

        Ts::IConnectionPointPtr       GetConnectionPoint(std::size_t index) const;


        boost::asio::io_service&    io_service();

    public:
        // override NetworkConnectionEventSink
        virtual void                OnConnected(NetworkConnectionEvent* pEvent);
        virtual void                OnDisconnected(NetworkConnectionEvent* pEvent);

    private:
        void                        IOThreadEntry();
        void                        ProcessPendingEvents();

    private:
        typedef std::list<IConnectionPointPtr> ConnectionPointList;

    private:
        mutable boost::recursive_mutex  m_mutexConnectionList; // Thread Safety: lock this mutex before accessing m_ConnectionList
        ConnectionPointList             m_ConnectionList;
        boost::thread*                  m_pAsioThread;

        boost::asio::io_service         m_io_service;

        DefaultFilter                   m_EventFilter;
        bool                            m_HasPendingDisconnectionEvent;
    };
}