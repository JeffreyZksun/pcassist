#pragma once

namespace Ts
{

    class ITCPClient
    {
    public:
        virtual ~ITCPClient(void){};

        virtual bool            ConnectToServer() = 0;
        virtual void            Close() = 0;
        virtual std::size_t     SendToServer(const WString& message) = 0;

        virtual bool            IsConnected() const = 0;

    };

}
