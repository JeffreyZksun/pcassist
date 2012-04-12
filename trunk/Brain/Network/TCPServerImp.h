#pragma once

#include <list>
#include <boost/thread.hpp>
#include <boost/asio.hpp>
#include "ConnectionGroupImp.h"
#include <boost/weak_ptr.hpp>

namespace Ts
{
    class TCPServer;
    class ConnectionPointImp;

    typedef boost::shared_ptr<ConnectionPointImp>   ConnectionPointImpPtr;
    typedef boost::shared_ptr<TCPServer>            TCPServerPtr;
    typedef boost::weak_ptr<TCPServer>              TCPServerBackPtr;

    class TCPServerImp
    {
    public:
        TCPServerImp(TCPServerBackPtr pSelf, unsigned short serverPort);
        ~TCPServerImp(void);

        TCPServerPtr    Self() const;

    public:

        bool            Start();
        void            Close();
        bool            BroadcastToClients(const WString& message);


    private:
        void            start_accept();
        void            handle_accept(const boost::system::error_code& error);


    private:
        TCPServerBackPtr        m_pSelf;

        ConnectionGroupImp      m_ConnectionGroup;

        unsigned short          m_ServerPort;
        ConnectionPointImpPtr   m_pListeningConnectionImp;
        boost::asio::ip::tcp::acceptor  m_acceptor;
    };
}