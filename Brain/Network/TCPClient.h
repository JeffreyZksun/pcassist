#pragma once

#include "ITCPClient.h"

namespace Ts
{
    class TCPClientImp;

    class TCPClient : public ITCPClient
    {
    public:
        TCPClient(const WString& serverIP, unsigned short serverPort);
        virtual ~TCPClient(void);

    public:
        virtual bool            ConnectToServer();
        virtual void            Close();
        virtual std::size_t     SendToServer(const WString& message);
    
        virtual bool            IsConnected() const;

    private:
        TCPClientImp* m_pImp;
    };
}
