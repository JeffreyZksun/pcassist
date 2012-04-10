#pragma once

namespace Ts
{

    class ITCPServer
    {
    public:
        virtual ~ITCPServer(void){};

        virtual bool            Start() = 0;
        virtual void            Close() = 0;
        virtual bool            BroadcastToClients(const WString& message) = 0;

    };

}
