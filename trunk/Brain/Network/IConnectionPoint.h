#pragma once
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

namespace Ts
{
    class IConnectionPoint : public boost::enable_shared_from_this<IConnectionPoint>
    {
    public:
        virtual ~IConnectionPoint(void){};

        virtual bool                ConnectToServer(const WString& serverIP, unsigned short serverPort) = 0;
        virtual void                Close() = 0;

        virtual void                Send(const WString& strData) = 0;

        virtual WString             GetRemoteIP() const = 0;
        virtual unsigned short      GetRemotePort() const = 0;
        virtual unsigned short      GetLocalPort() const = 0;
        virtual bool                IsConnected() const = 0;
    };
}
