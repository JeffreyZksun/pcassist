#pragma once

#include "ITCPClient.h"
#include <boost/shared_ptr.hpp>

namespace Ts
{
    class TCPClient;
    class TCPClientImp;
    typedef boost::shared_ptr<TCPClientImp>            TCPClientImpPtr;
    typedef boost::shared_ptr<TCPClient>               TCPClientPtr;

    class TCPClient : public ITCPClient
    {
    public:
        virtual ~TCPClient(void);

        static TCPClientPtr Create(const WString& serverIP, unsigned short serverPort);

    protected:
        TCPClient();

    public:
        virtual bool            ConnectToServer();
        virtual void            Close();
        virtual void            SendToServer(const WString& message);
    
        virtual bool            IsConnected() const;

    private:
        TCPClientImpPtr         m_pImp;
    };
}
