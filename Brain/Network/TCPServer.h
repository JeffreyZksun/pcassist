#pragma once

#include "ITCPServer.h"
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

namespace Ts
{

    class TCPServerImp;
    class TCPServer;
    typedef boost::shared_ptr<TCPServerImp> TCPServerImpPtr;
    typedef boost::shared_ptr<TCPServer> TCPServerPtr;

    class TCPServer : public ITCPServer
    {
    public:
        virtual ~TCPServer(void);

        static TCPServerPtr Create(unsigned short serverPort);

    protected:
        TCPServer();

    public:
        virtual bool            Start();
        virtual void            Close();
        virtual bool            BroadcastToClients(const WString& message);


    private:
        TCPServerImpPtr m_pImp;
    };

}