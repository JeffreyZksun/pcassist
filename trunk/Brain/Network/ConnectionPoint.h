#pragma once

#include "IConnectionPoint.h"

namespace Ts
{

    class ConnectionPointImp;
    class ConnectionPoint;

    typedef boost::shared_ptr<ConnectionPointImp>   ConnectionPointImpPtr;
    typedef boost::shared_ptr<ConnectionPoint>      ConnectionPointPtr;

    class ConnectionPoint : public IConnectionPoint
    {
    public:
        virtual ~ConnectionPoint(void);

        static ConnectionPointPtr Create(ConnectionPointImpPtr pImp);

    protected:
        ConnectionPoint(); // Disable this

    public:
        virtual bool                ConnectToServer(const WString& serverIP, unsigned short serverPort);
        virtual void                Close();

        virtual void                Send(const WString& strData);

        virtual WString             GetRemoteIP() const;
        virtual unsigned short      GetRemotePort() const;
        virtual unsigned short      GetLocalPort() const;
        virtual bool                IsConnected() const;



    private:

        ConnectionPointImpPtr         m_pImp;
    };

}