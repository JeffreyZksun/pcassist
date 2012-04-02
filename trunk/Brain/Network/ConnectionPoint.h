#pragma once

#include "IConnectionPoint.h"

namespace Ts
{

    class ConnectionPointImp;

    class ConnectionPoint : public IConnectionPoint
    {
    public:
        ConnectionPoint();

        virtual ~ConnectionPoint(void);

    public:
        virtual bool                Accept(unsigned short serverPort); // work as server
        virtual bool                ConnectToServer(const WString& serverIP, unsigned short serverPort); // work as client
        virtual bool                IsConnected() const;
    
        virtual std::size_t         Send(const WString& strData);
        virtual bool                Receive(WString& strData);
        virtual void                Receive_Asyc();

        virtual WString             GetRemoteIP();

        virtual bool                Close();

    private:

        ConnectionPointImp*     m_pImp;
    };

}