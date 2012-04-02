#pragma once

#include "ITCPServer.h"

namespace Ts
{

    class TCPServerImp;

    class TCPServer : public ITCPServer
    {
    public:
        TCPServer(unsigned short serverPort);
        virtual ~TCPServer(void);

     public:
        virtual bool            StartListen_Asyc();
        virtual void            Close();
        virtual bool            BroadcastToClients(const WString& message);


    private:
        TCPServerImp* m_pImp;
    };

}