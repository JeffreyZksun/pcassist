#pragma once

#include <boost/asio.hpp>

#include "ConnectionGroupImp.h"

namespace Ts
{
    class IConnectionPoint;
    class TCPClient;


    class TCPClientImp
    {
    public:
        TCPClientImp(TCPClient* pSelf, const WString& serverIP, unsigned short serverPort);
        ~TCPClientImp(void);

        TCPClient*    Self() const;

    public:

        bool                    ConnectToServer();
        virtual void            Close();
        void                    SendToServer(const WString& message);

        bool                    IsConnected() const;

    private:
        TCPClient*          m_pSelf;

        ConnectionGroupImp  m_ConnectionGroup;

        WString             m_ServerIP;
        unsigned short      m_ServerPort;
    };
}