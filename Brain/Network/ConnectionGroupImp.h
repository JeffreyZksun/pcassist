#pragma once

#include <boost/asio.hpp>
#include <boost/thread.hpp>

namespace Ts
{
    class IConnectionPoint;

    class ConnectionGroupImp
    {
    public:
        ConnectionGroupImp();
        ~ConnectionGroupImp(void);

        void                        Start();
        void                        Close();

        void                        Add(Ts::IConnectionPoint* pConnectionPoint);
        void                        Send(const WString& message);

        Ts::IConnectionPoint*       GetConnectionPoint(std::size_t index) const;


        boost::asio::io_service&    io_service();

    private:
        void                        IOThreadEntry();

    private:
        typedef std::list<IConnectionPoint*> ConnectionPointList;

    private:
        ConnectionPointList             m_ConnectionList;
        boost::thread*                  m_pAsioThread;

        boost::asio::io_service         m_io_service;
    };
}