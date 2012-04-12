#pragma once

#include <boost/asio.hpp>

#include "ConnectionGroupImp.h"
#include <boost/weak_ptr.hpp>

namespace Ts
{
    class TCPClient;

    typedef boost::shared_ptr<TCPClient>            TCPClientPtr;
    typedef boost::weak_ptr<TCPClient>              TCPClientBackPtr;

    class TCPClientImp
    {
    public:
        TCPClientImp(TCPClientBackPtr pSelf, const WString& serverIP, unsigned short serverPort);
        ~TCPClientImp(void);

        TCPClientPtr            Self() const;

    public:

        bool                    ConnectToServer();
        virtual void            Close();
        void                    SendToServer(const WString& message);

        bool                    IsConnected() const;

    private:
        TCPClientBackPtr    m_pSelf;

        ConnectionGroupImp  m_ConnectionGroup;

        WString             m_ServerIP;
        unsigned short      m_ServerPort;
    };
}