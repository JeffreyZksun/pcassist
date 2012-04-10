#pragma once

#include <list>
#include <boost/thread.hpp>
#include <boost/asio.hpp>

#include "ConnectionGroupImp.h"

namespace Ts
{
    class IConnectionPoint;
    class TCPServer;
    class ConnectionPointImp;

    class TCPServerImp
    {
    public:
        TCPServerImp(TCPServer* pSelf, unsigned short serverPort);
        ~TCPServerImp(void);

        TCPServer*      Self() const;

    public:

        bool            Start();
        void            Close();
        bool            BroadcastToClients(const WString& message);


    private:
        void            start_accept();
        void            handle_accept(ConnectionPointImp* pImp,
            const boost::system::error_code& error);

    private:
        typedef std::list<IConnectionPoint*> ConnectionPointList;

    private:
        TCPServer*              m_pSelf;

        ConnectionGroupImp      m_ConnectionGroup;

        unsigned short          m_ServerPort;
        ConnectionPointImp*     m_pListeningConnectionImp;
        boost::asio::ip::tcp::acceptor  m_acceptor;
    };
}