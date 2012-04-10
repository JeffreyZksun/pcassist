#pragma once

#include "IConnectionPoint.h"

namespace Ts
{

    class ConnectionPointImp;

    class ConnectionPoint : public IConnectionPoint
    {
    public:
        ConnectionPoint(ConnectionPointImp* pImp);

        virtual ~ConnectionPoint(void);

    public:
        virtual bool                ConnectToServer(const WString& serverIP, unsigned short serverPort);
        virtual void                Close();

        virtual void                Send(const WString& strData);

        virtual WString             GetRemoteIP() const;
        virtual unsigned short      GetRemotePort() const;
        virtual unsigned short      GetLocalPort() const;
        virtual bool                IsConnected() const;



    private:

        ConnectionPointImp*         m_pImp;
    };

}